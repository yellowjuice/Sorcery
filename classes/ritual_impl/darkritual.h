#include "../ritual.h"
#ifndef DARKRITUAL_H
#define DARKRITUAL_H

extern const std::string darkRitualAbilityName;

class DarkRitual : public Ritual {
    class DarkRitualAbility : public Ability {
      public:
        DarkRitualAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        DarkRitualAbility *clone() override;
    };

  public:
    DarkRitual(int player);
};

#endif