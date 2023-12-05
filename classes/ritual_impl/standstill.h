#include "../ritual.h"
#ifndef STANDSTILL_H
#define STANDSTILL_H

extern const std::string standstillAbilityName;

class Standstill : public Ritual {
    
    class StandstillAbility : public Ability {
      public:
        StandstillAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI);
        StandstillAbility *clone();
    };
    
  public:
    Standstill(int player);
};

#endif