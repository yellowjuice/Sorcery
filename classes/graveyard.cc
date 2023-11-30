#include "graveyard.h"

Graveyard::Graveyard(Observer *owner, int player) :
    minions{std::vector<Minion *>()}, owner{owner}, player{player} { }

Graveyard::~Graveyard() {
    while (!minions.empty()) {
        delete minions.back();
        minions.pop_back();
    }
}

bool Graveyard::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player != player) return owner->request(requests, c);
    if (r.target_location != Location::GRAVEYARD) return owner->request(requests, c);
    switch(r.cmd) {
        case Request::Add:
            {
            if (c == nullptr) return false;
            if (c->getType() != Card::MINION) return false;
            Minion *m = dynamic_cast<Minion *>(c);
            Minion *temp = m->unenchant();
            while (m != temp) {
                delete m;
                m = temp;
                temp = m->unenchant();
            }
            minions.push_back(m);
            break;
            }
        case Request::Remove: // only have permission to remove top
            if (!minions.empty()) {
                minions.pop_back();
            }
            return true;
        case Request::Store: // only have permission to store top
            c = minions.back();
            break;
        case Request::Success:
            requests->erase(requests->begin());
            request(requests, c);
            return true;
        case Request::Fail:
            return false;
        default:
            return false;
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

bool Graveyard::notify(Notification n) { return true; }

card_template_t Graveyard::getAscii() const {
    if (minions.empty()) return CARD_TEMPLATE_BORDER;
    return minions.back()->getAscii();
}