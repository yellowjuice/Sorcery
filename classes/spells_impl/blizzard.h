#include "../spell.h"
#ifndef BLIZZARD_H
#define BLIZZARD_H

extern const std::string blizzardAbilityName;

class Blizzard : public Spell {
    class BlizzardAbility : public Ability {
      public:
        BlizzardAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    Blizzard(int player);
};

#endif