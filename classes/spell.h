#include "card.h"
#ifndef SPELL_H
#define SPELL_H

class Spell : public Card {
    Ability *a;

  public:
    Spell(std::string name, int cost, int player, Ability *a);
    ~Spell() override;

    bool play(int p = 0, Location l = Location::NONE, int i = -1);

    bool request(std::vector<Request> *v, Card *storage) override;
    void notify(Notification n) override;

    card_template_t getAscii() const override;

    Spell *clone() const override;
};

#endif