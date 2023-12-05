#include "magicfatigue.h"

const std::string magicFatigueAbilityName = "Enchanted Minion's activated ability costs 2 more";


MagicFatigue::MagicFatigue(int player) :
    Enchantment("Magic Fatigue", 1, player, false, new Ability(),
                new Ability(false, magicFatigueAbilityName, 0), new Ability(), new Ability(), new Ability()) { }

int MagicFatigue::activeCostModifier(int x) { return x + 2; }