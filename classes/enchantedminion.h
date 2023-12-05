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

    bool hasActive() const override;
    int activeCost() const override;

    Minion *unenchant() override;
    
    Minion *clone() const override;

    void addAtk(int a) override;
    void loseDef(int d) override;

    void inspectEnchants(std::ostream &out, std::vector<std::vector<card_template_t>> &v, int mod, bool print = false) const override;
    void inspectMe(std::ostream &out) const override;

    card_template_t getAsciiAlt(int atk, int def) const override;
};

#endif