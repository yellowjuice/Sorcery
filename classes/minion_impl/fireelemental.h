#include "../minion.h"
#ifndef FIREELEMENTAL_H
#define FIREELEMENTAL_H

extern const std::string fireElementalAbilityName;

class FireElemental : public Minion {

    class FireElementalAbility : public Ability {
      public:
        FireElementalAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        FireElementalAbility *clone() override;
    };

  public:
    FireElemental(int player);

};

#endif