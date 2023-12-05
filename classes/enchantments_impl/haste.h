#include "../enchantment.h"
#ifndef HASTE_H
#define HASTE_H

extern const std::string hasteAbilityName;

class Haste : public Enchantment {
    class HasteAbilityStart : public Ability {
      public:
        HasteAbilityStart();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI);
    };

    class HasteAbilityEnd : public Ability {
      public:
        HasteAbilityEnd();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI);
    };

    class HasteAbilityOnPlay : public Ability {
      public:
        HasteAbilityOnPlay();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI);
    };
  public:
    Haste(int player);
};

#endif