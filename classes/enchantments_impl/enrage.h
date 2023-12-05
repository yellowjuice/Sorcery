#include "../enchantment.h"
#ifndef ENRAGE_H
#define ENRAGE_H

class Enrage : public Enchantment {
  public:
    Enrage(int player);

    int atkModifier(int a) override;
    int defModifier(int d) override;
};

#endif