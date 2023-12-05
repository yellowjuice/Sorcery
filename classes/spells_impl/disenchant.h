#include "../spell.h"
#ifndef DISENCHANT_H
#define DISENCHANT_H

extern const std::string disenchantAbilityName;

class Disenchant : public Spell {
    class DisenchantAbility : public Ability {
      public:
        DisenchantAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    Disenchant(int player);
};

#endif