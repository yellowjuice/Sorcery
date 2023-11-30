#include "board.h"
#include "spell.h"
#include "enchantment.h"
#include "enchantedminion.h"

Board::Board(Observer *owner, int player) :
    minions{std::vector<Minion *>()}, ritual{nullptr}, owner{owner}, player{player} { }

Board::~Board() {
    delete ritual;
    while (!minions.empty()) {
        delete minions[0];
        minions.erase(minions.begin());
    }
}

// POTENTIALLY BUGGY, TEST
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
                minions[r.target_index] = minions[r.target_index]->enchant(dynamic_cast<Enchantment *>(c));
                break;
            }

            // playing rituals (note: rituals are neither arged nor targeted)
            if (c->getType() == Card::Type::RITUAL) {
                if (ritual != nullptr) delete ritual;
                ritual = dynamic_cast<Ritual *>(c);
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
                break;
            }
        case Request::Remove:
            // invalid input
            if (r.target_index < 0) return false;
            if (r.target_index > 5) return false;
            if (r.target_index == 5 && ritual == nullptr) return false;
            if (r.target_index == 5) {
                delete ritual;
                break;
            }
            if (r.target_index >= static_cast<int>(minions.size())) return false;
            minions[r.target_index]->setIndex(-1);
            minions.erase(minions.begin() + r.target_index);
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
            if (r.target_index >= 0 && r.target_index < static_cast<int>(minions.size()) 
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
        default:
            if (r.target_index == 5) {
                return ritual->request(requests, c);
            }
            if (r.target_index >= static_cast<int>(minions.size())) return false;
            if (r.target_index < 0) return false;
            return minions[r.target_index]->request(requests, c);
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

// POTENTIALLY BUGGY, TEST
bool Board::notify(Notification n) {
    
    bool retval = true;
    for (auto x : minions) {
        retval = x->notify(n) && retval;
    }
    if (ritual != nullptr) {
        retval = ritual->notify(n) && retval;
    }
    if (n.sender_player == player) {
        retval = owner->notify(n) && retval;
    }
    return retval;
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
    if (minions.size() < i) {
        minions.at(i)->inspect(out);
        return true;
    }
    return false;
}