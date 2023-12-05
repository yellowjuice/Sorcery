#include "../spell.h"
#ifndef RECHARGE_H
#define RECHARGE_H

extern const std::string rechargeAbilityName;

class Recharge : public Spell {
    class RechargeAbility : public Ability {
      public:
        RechargeAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    Recharge(int player);
};

#endif