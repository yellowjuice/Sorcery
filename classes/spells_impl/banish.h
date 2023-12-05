#include "../spell.h"
#ifndef BANISH_H
#define BANISH_H

extern const std::string banishAbilityName;

class Banish : public Spell {
    class BanishAbility : public Ability {
      public:
        BanishAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    Banish(int player);
};

#endif