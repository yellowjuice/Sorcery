#include "../ritual.h"
#ifndef AURAOFPOWER_H
#define AURAOFPOWER_H

extern const std::string auraOfPowerAbilityName;

class AuraOfPower : public Ritual {
    class AuraOfPowerAbility : public Ability {
      public:
        AuraOfPowerAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI);
        AuraOfPowerAbility *clone();
    };
    
  public:
    AuraOfPower(int player);
};

#endif