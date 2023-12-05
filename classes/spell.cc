#include "spell.h"

Spell::Spell(std::string name, int cost, int player, Ability *a) :
    Card(Card::Type::SPELL, name, cost, player), a{a} { }

Spell::~Spell() {
    delete a;
}

bool Spell::play(int p, Location l, int i) {
        return requestOwner(a->get(p, l, i, getPlayer(), getLocation(), -1), nullptr);
}

bool Spell::request(std::vector<Request> *v, Card *storage) { 
    if ((*v)[0].cmd == Request::Store) {
        v->erase(v->begin());
        return requestOwner(v, this);
    }
    return false;
 }
void Spell::notify(Notification n) { }

card_template_t Spell::getAscii() const {
    return display_spell(getName(), getCost(), a->getDescription());
}

Spell *Spell::clone() const {
    Spell *retval = new Spell(getName(), getCost(), getPlayer(), a->clone());
    retval->setLocation(getLocation());
    retval->setOwner(getOwner());
    return retval;
}