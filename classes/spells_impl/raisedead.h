#include "../spell.h"
#ifndef RAISEDEAD_H
#define RAISEDEAD_H

extern const std::string raiseDeadAbilityName;

class RaiseDead : public Spell {
    class RaiseDeadAbility : public Ability {
      public:
        RaiseDeadAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
    };
  public:
    RaiseDead(int player);
};

#endif