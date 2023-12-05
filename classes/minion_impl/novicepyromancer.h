#include "../minion.h"
#ifndef NOVICEPYROMANCER_H
#define NOVICEPYROMANCER_H

extern const std::string novicePyromancerAbilityName;

class NovicePyromancer : public Minion {
    class NovicePyromancerAbility : public Ability {
      public:
        NovicePyromancerAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };

  public:
    NovicePyromancer(int player);

};

#endif