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
                minions.back()->setDefense(r.arg);
                minions.pop_back();
            }
            return true;
        case Request::Store: // only have permission to store top
            if (!minions.empty()){
                c = minions.back();
                break;
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
            return false;
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

void Graveyard::notify(Notification n) { }

card_template_t Graveyard::getAscii() const {
    if (minions.empty()) return CARD_TEMPLATE_BORDER;
    return minions.back()->getAscii();
}