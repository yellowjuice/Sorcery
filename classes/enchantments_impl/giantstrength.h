#include "../enchantment.h"
#ifndef GIANTSTRENGTH_H
#define GIANTSTRENGTH_H

class GiantStrength : public Enchantment {
  public:
    GiantStrength(int player);

    int atkModifier(int a) override;
    int defModifier(int d) override;
};

#endif