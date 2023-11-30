#include "card.h"

Card::Card() : 
    Observer(Location::NONE), type{Card::Type::NONE}, name{""}, cost{0}, owner{nullptr}, player{0} { }

Card::Card(Type type, std::string name, int cost, int player) :
    Observer(Location::NONE), type{type}, name{name}, cost{cost}, owner{nullptr}, player{player} { }

bool Card::requestOwner(std::vector<Observer::Request> *v, Card *storage) {
    return owner->request(v, storage);
}

bool Card::notifyOwner(Notification n) {
    return owner->notify(n);
}

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
