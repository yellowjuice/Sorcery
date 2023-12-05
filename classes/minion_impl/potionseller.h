#include "../minion.h"
#ifndef POTIONSELLER_H
#define POTIONSELLER_H

extern const std::string potionSellerAbilityName;

class PotionSeller : public Minion {
    class PotionSellerAbility : public Ability {
      public:
        PotionSellerAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        PotionSellerAbility *clone() override;
    };
  public:
    PotionSeller(int player);
};

#endif