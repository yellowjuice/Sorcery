#include "card.h"

Card::Card() : 
    Observer(Location::NONE), type{Card::Type::NONE}, name{""}, cost{0}, owner{nullptr}, player{0} { }

Card::Card(Type type, std::string name, int cost, int player) :
    Observer(Location::NONE), type{type}, name{name}, cost{cost}, owner{nullptr}, player{player} { }

bool Card::requestOwner(std::vector<Observer::Request> *v, Card *storage) {
    return owner->request(v, storage);
}

void Card::notifyOwner(Notification n) {
    owner->notify(n);
}

Observer *Card::getOwner() const { return owner; }

Card::Type Card::getType() const { return type; }
std::string Card::getName() const { return name; }
int Card::getCost() const { return cost; }
int Card::getPlayer() const { return player; }

void Card::setOwner(Observer *o) {
    owner = o;
}

std::ostream &operator<<(std::ostream &out, const Card &c) {
    card_template_t outer = c.getAscii();
    for (auto x : outer) {
        out << x << std::endl;
    }
    return out;
}

std::vector<Card::Request> *Card::Ability::get(int p, Location l, int i, int myP, Location myL, int myI) {
    return new std::vector<Request>; 
}

