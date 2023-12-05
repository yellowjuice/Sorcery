#include "board.h"
#include "spell.h"
#include "enchantment.h"
#include "enchantedminion.h"

Board::Board(Observer *owner, int player) :
    minions{std::vector<Minion *>()}, ritual{nullptr}, owner{owner}, player{player} { }

Board::~Board() {
    delete ritual;
    while (!minions.empty()) {
        Minion *m = minions[0];
        minions.erase(minions.begin());
        Minion *temp = m->unenchant();
        while (m != temp) {
            delete m;
            m = temp;
            temp = m->unenchant();
        }
        delete m;
    }
}

// POTENTIALLY BUGGY, TEST TEST TEST
bool Board::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player != player) return owner->request(requests, c);
    if (r.target_location != Location::BOARD) return owner->request(requests, c);
    switch (r.cmd) {
        case Request::Add:
            // invalid input
            if (c == nullptr) return false;
            // playing spells (note: spells take arg as argument, targeting is done through hand)
            if (c->getType() == Card::Type::SPELL) {
                c->setLocation(Location::BOARD);
                c->setOwner(this);
                if (dynamic_cast<Spell *>(c)->play(r.arg_player, r.arg_location, r.arg_index)) {
                    delete c;
                    break;
                }
                else return false;
            }
            // playing enchantments (note: enchantments are targeted to minion, not arged)
            if (r.target_index >= 0 && r.target_index < static_cast<int>(minions.size()) 
                                    && c->getType() == Card::Type::ENCHANTMENT) {
                c->setLocation(Location::BOARD);
                c->setOwner(this);
                Enchantment *d = dynamic_cast<Enchantment *>(c);
                minions[r.target_index] = minions[r.target_index]->enchant(d);
                if (!d->getOnPlay()->isEmpty()) {
                    std::vector<Request> *rs = d->getOnPlay()->get(r.target_player, r.target_location, r.target_index,
                                                r.target_player, r.target_location, r.target_index);
                    request(rs, nullptr);
                    delete rs;
                }
                break;
            }

            // playing rituals (note: rituals are neither arged nor targeted)
            if (c->getType() == Card::Type::RITUAL) {
                if (ritual != nullptr) delete ritual;
                ritual = dynamic_cast<Ritual *>(c);
                ritual->setOwner(this);
                ritual->setLocation(Location::BOARD);
                break;
            }
            // playing minions (not: minions are neither arged nor targeted)
            else {
                if (c->getType() != Card::Type::MINION) return false;
                if (minions.size() >= 5) return false;
                c->setLocation(Location::BOARD);
                c->setOwner(this);
                minions.push_back(dynamic_cast<Minion *>(c));
                minions[minions.size() - 1]->setIndex(minions.size() - 1);
                notify(Notification{Notification::Trigger::Enter, player, 
                                    Location::BOARD, static_cast<int>(minions.size() - 1), -1});
                break;
            }
        case Request::Remove:
            // invalid input
            if (r.target_index < 0) return false;
            if (r.target_index > 5) return false;
            if (r.target_index == 5 && ritual == nullptr) return false;
            if (r.target_index == 5) {
                delete ritual;
                ritual = nullptr;
                break;
            }
            if (r.target_index >= static_cast<int>(minions.size())) return false;
            notify(Notification{Notification::Trigger::Exit, player, Location::BOARD, r.target_index, -1});
            minions[r.target_index]->setIndex(-1);
            minions.erase(minions.begin() + r.target_index);
            for (int i = r.target_index; i < static_cast<int>(minions.size()); ++i) {
                minions[i]->setIndex(i);
            }
            break;
        case Request::Unenchant:
            if (r.target_index >= 0 && r.target_index < static_cast<int>(minions.size())) {
                Minion *temp = minions[r.target_index];
                minions[r.target_index] = minions[r.target_index]->unenchant();
                delete temp;
                break;
            }
            else return false;
        case Request::Play:
            return false;
        case Request::UseAbility:
            if (r.target_index >= 0 && r.target_index < static_cast<int>(minions.size()) && minions.at(r.target_index)->hasActive() 
                && minions[r.target_index]->useActive(r.arg_player, r.arg_location, r.arg_index)) {
                break;
            }
            else return false;
        case Request::UseAttack:
            if (r.target_index >= 0 && r.target_index < static_cast<int>(minions.size())) {
                if (r.arg_location == Location::PLAYER && minions[r.target_index]->attackPlayer()) {
                    break;
                }
                else if (r.arg_location == Location::BOARD
                         && minions[r.target_index]->attackMinion(r.arg_index)) {
                    break;
                }
            }
            return false;
        case Request::Success:
            requests->erase(requests->begin());
            request(requests, c);
            return true;
        case Request::Fail:
            return false;
        case Request::Copy:
            c = c->clone();
            break;
        case Request::Delete:
            delete c;
            break;
        case Request::IfFail:
            {
            requests->erase(requests->begin());
            if (requests->empty()) return true;
            std::vector<Request> temp;
            for (int j = 0; j < r.arg && !requests->empty(); ++j) {
                temp.push_back((*requests)[0]);
                requests->erase(requests->begin());
            }
            bool v = request(requests, c);
            if (!v) {
                request(&temp, c);
                return false;
            }
            return true;
            }
        default:
            if (r.target_index == 6) {
                std::vector<Minion *> temp;
                for (Minion *x : minions) {
                    temp.push_back(x);
                }
                for (Minion *x : temp) {
                    Request temp2 = Request((*requests)[0]);
                    temp2.target_index = x->getIndex();
                    std::vector<Request> tV;
                    tV.push_back(temp2);
                    x->request(&tV, nullptr);
                }
                requests->erase(requests->begin());
                return request(requests, c);
            }
            if (r.target_index == 5 && ritual != nullptr) {
                return ritual->request(requests, c);
            }
            if (r.target_index == 5) return false;
            if (r.target_index >= static_cast<int>(minions.size())) return false;
            if (r.target_index < 0) return false;
            return minions[r.target_index]->request(requests, c);
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

// POTENTIALLY BUGGY, TEST
void Board::notify(Notification n) {
    
    for (auto x : minions) {
        x->notify(n);
    }
    if (ritual != nullptr) {
        ritual->notify(n);
    }
    if (n.sender_player == player) {
        owner->notify(n);
    }
}

card_template_t Board::ritualAscii() const {
    if (!ritual) return CARD_TEMPLATE_BORDER;
    return ritual->getAscii();
}

std::ostream &operator<<(std::ostream &out, const Board &b) {
    int num = b.minions.size();
    std::vector<card_template_t> cardAscii;
    for (int i = 0; i < num; ++i) {
        cardAscii.push_back(b.minions.at(i)->getAscii());
    }
    for (int i = num; i < 5; ++i) {
        cardAscii.push_back(CARD_TEMPLATE_BORDER);
    }
    std::vector<card_template_t::iterator> iterators;
    for (auto &x : cardAscii) {
        iterators.push_back(x.begin());
    }
    for ( ; iterators[0] != cardAscii[0].end() ; ) {
        out << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (auto &x : iterators) {
            out << (*x);
            ++x;
        }
        out << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }
    return out;
}

bool Board::inspect(std::ostream &out, int i) const {
    if (i < static_cast<int>(minions.size())) {
        minions.at(i)->inspect(out);
        return true;
    }
    return false;
}

int Board::numMinions() const {
    return static_cast<int>(minions.size());
}

int Board::useCost(int i) const {
    return minions.at(i)->activeCost();
}