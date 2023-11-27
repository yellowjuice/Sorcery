#include "card.h"
#ifndef SPELL_H
#define SPELL_H

class Spell : public Card {
    Ability a;

  public:
    Spell();
    Spell(std::string name, int cost, int player, Ability a);

    bool play(int p = 0, Location l = Location::NONE, int i = -1);

    bool request(std::vector<Request> *v, Card *storage) override;
    bool notify(Notification n) override;
};

#endif