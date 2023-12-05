#include "../enchantment.h"
#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H

extern const std::string magicFatigueAbilityName;

class MagicFatigue : public Enchantment {

  public:
    MagicFatigue(int player);
    int activeCostModifier(int x) override;
};

#endif