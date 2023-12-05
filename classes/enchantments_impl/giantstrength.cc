#include "giantstrength.h"

GiantStrength::GiantStrength(int player) :
    Enchantment("Giant Strength", 1, player, false, new Ability(),
                new Ability(), new Ability(), new Ability(), new Ability(),
                "+2", "+2", true) { }

int GiantStrength::atkModifier(int a) { return a + 2; }
int GiantStrength::defModifier(int d) { return d + 2; }