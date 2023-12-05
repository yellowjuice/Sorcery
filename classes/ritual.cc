#include "ritual.h"

Ritual::Ritual(std::string name, int cost, int player, int charges, 
                int chargeCost, Notification::Trigger trigger, Ability *passive) :
    Card(Card::Type::RITUAL, name, cost, player), charges{charges}, 
    chargeCost{chargeCost}, trigger{trigger}, passive{passive} { }

Ritual::~Ritual() {
    delete passive;
}

bool Ritual::request(std::vector<Request> *r, Card *c) {
    while (!r->empty() && r->at(0).target_player == getPlayer()
            && r->at(0).target_location == getLocation() && r->at(0).target_index == 5) {
        switch (r->at(0).cmd) {
            case Request::Store:
                c = this;
                break;
            case Request::GetAction:
                charges += r->at(0).arg;
                break;
            default:
                break;
        }
        r->erase(r->begin());
    }
    return requestOwner(r, c);
}

void Ritual::notify(Notification n) {
    if (n.trigger == trigger && charges >= chargeCost) {
        std::vector<Request> *notifier = (n.trigger == Notification::Start || n.trigger == Notification::End) ? 
                                                passive->get(n.arg, 
                                                            n.sender_location, 
                                                            n.sender_index,
                                                            getPlayer(), getLocation(),
                                                            5) :
                                                passive->get(n.sender_player, 
                                                            n.sender_location, 
                                                            n.sender_index,
                                                            getPlayer(), getLocation(),
                                                            5);
        if (!notifier->empty()) {
            requestOwner(notifier, passive->getPtr(getPlayer()));
            delete notifier;
            charges -= chargeCost;
        }
    }
}

card_template_t Ritual::getAscii() const {
    return display_ritual(getName(), getCost(), chargeCost, passive->getDescription(), charges);
}

Ritual *Ritual::clone() const {
    Ritual *retval = new Ritual(getName(), getCost(), getPlayer(), charges, chargeCost, trigger, passive->clone());
    retval->setLocation(getLocation());
    retval->setOwner(getOwner());
    return retval;
}