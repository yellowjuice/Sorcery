#include "spell.h"

Spell::Spell() :
    Card(Type::SPELL, "", 0, 0), a{Ability(false, nullptr)} { }

Spell::Spell(std::string name, int cost, int player, Ability a) :
    Card(Card::Type::SPELL, name, cost, player), a{a} { }

bool Spell::play(int p, Location l, int i) {
        return requestOwner(a.get(p, l, i), nullptr);
}

bool Spell::request(std::vector<Request> *v, Card *storage) { return true; }
bool Spell::notify(Notification n) { return true; }