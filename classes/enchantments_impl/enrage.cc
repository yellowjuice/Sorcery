#include "enrage.h"

Enrage::Enrage(int player) :
    Enchantment("Enrage", 2, player, false, new Ability(),
                new Ability(), new Ability(), new Ability(), new Ability(),
                "*2", "*2", true) { }

int Enrage::atkModifier(int a) { return a * 2; }
int Enrage::defModifier(int d) { return d * 2; }