#include "../spell.h"
#ifndef UNSUMMON_H
#define UNSUMMON_H

extern const std::string unsummonAbilityName;

class Unsummon : public Spell {
    class UnsummonAbility : public Ability {
      public:
        UnsummonAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    Unsummon(int player);
};

#endif