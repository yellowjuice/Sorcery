#include "minion.h"
#ifndef ENCHANTEDMINION_H
#define ENCHANTEDMINION_H

class EnchantedMinion : public Minion {
    Minion *m;
    Enchantment *e;

  public:
    EnchantedMinion(Minion *m, Enchantment *e);
    ~EnchantedMinion() override;

    bool useActive(int p, Location l, int i) override;
    bool useStart(int p) override;
    bool useEnd(int p) override;
    bool useEnter(int p, Location l, int i) override;
    bool useExit(int p, Location l, int i) override;

    Minion *unenchant() override;
};

#endif