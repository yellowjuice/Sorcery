#include "hand.h"
#include "minion.h"

Hand::Hand(Observer *owner, int player) :
    cards{std::vector<Card *>()}, owner{owner}, player{player} { }

Hand::~Hand() {
    while (!cards.empty()) {
        delete cards[0];
        cards.erase(cards.begin());
    }
}

int Hand::numCards() const { return static_cast<int>(cards.size()); }

bool Hand::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player != player) return owner->request(requests, c);
    if (r.target_location != Location::HAND) return owner->request(requests, c);
    switch(r.cmd) {
        case Request::Add:
            if (c == nullptr) return false;
            if (numCards() >= 5) return false;
            if (c->getType() == Card::MINION) {
                Minion *m = dynamic_cast<Minion *>(c);
                Minion *temp = m->unenchant();
                while (temp != m) {
                    delete m;
                    m = temp;
                    temp = m->unenchant();
                }
                c = m;
            }
            cards.push_back(c);
            break;
        case Request::Remove:
            if (r.target_index < 0) return false;
            if (r.target_index >= static_cast<int>(cards.size())) return false;
            cards.erase(cards.begin() + r.target_index);
            break;
        case Request::Play:
            {
            if (r.target_index < 0) return false;
            if (r.target_index >= static_cast<int>(cards.size())) return false;
            Card *send = cards[r.target_index];
            
            std::vector<Request> v;
            if (r.arg_player != player && (send->getType() == Card::MINION ||
                                           send->getType() == Card::RITUAL)) return false;
            if (send->getType() == Card::MINION || send->getType() == Card::RITUAL) {
                v.push_back(Request{player, Location::BOARD, 0, 
                                    player, Location::HAND, -1,
                                    Request::Add});
            }
            else if (send->getType() == Card::ENCHANTMENT) {
                v.push_back(Request{r.arg_player, Location::BOARD, r.arg_index, 
                                    player, Location::HAND, -1,
                                    Request::Add});
            }
            else if (send->getType() == Card::SPELL) {
                v.push_back(Request{player, Location::BOARD, -1,
                                    player, Location::HAND, -1,
                                    Request::Add, r.arg,
                                    r.arg_player, r.arg_location, r.arg_index});
            }
            if (request(&v, send)) {
                cards.erase(cards.begin() + r.target_index);
                break;
            }
            return false;
            }
        case Request::Success:
            requests->erase(requests->begin());
            request(requests, c);
            return true;
        case Request::Fail:
            return false;
        case Request::Store:
            if (r.target_index < 0) return false;
            if (r.target_index >= static_cast<int>(cards.size())) return false;
            c = cards[r.target_index];
            break;
        default:
            return false;
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

bool Hand::notify(Notification n) {
    return true;
}

std::ostream &operator<<(std::ostream &out, const Hand &h) {
    int num = h.numCards();
    if (num == 0) return out;
    std::vector<card_template_t> cardAscii;
    for (int i = 0; i < num; ++i) {
        cardAscii.push_back(h.cards.at(i)->getAscii());
    }
    std::vector<card_template_t::iterator> iterators;
    for (auto &x : cardAscii) {
        iterators.push_back(x.begin());
    }
    for ( ; iterators[0] != cardAscii[0].end() ; ) {
        for (auto &x : iterators) {
            out << (*x);
            ++x;
        }
        out << std::endl;
    }
    return out;
}