#include "ritual.h"

Ritual::Ritual(std::string name, int cost, int player, int charges, 
                int chargeCost, Notification::Trigger trigger, Ability passive) :
    Card(Card::Type::RITUAL, name, cost, player), charges{charges}, 
    chargeCost{chargeCost}, trigger{trigger}, passive{passive} { }

bool Ritual::request(std::vector<Request> *r, Card *c) {
    while (!r->empty() && r->at(0).target_player == getPlayer()
            && r->at(0).target_location == getLocation() && r->at(0).target_index == 5) {
        switch (r->at(0).cmd) {
            case Request::Store:
                c = this;
                break;
            case Request::GiveAction:
                charges += r->at(0).arg;
                break;
            default:
                break;
        }
        r->erase(r->begin());
    }
    return requestOwner(r, c);
}

bool Ritual::notify(Notification n) {
    if (n.trigger == trigger) {
        std::vector<Request> *notifier = passive.get(n.sender_player, 
                                                     n.sender_location, 
                                                     n.sender_index);
        bool retval = requestOwner(notifier, passive.getPtr());
        delete notifier;
        return retval;
    }
    return true;
}