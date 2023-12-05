#include "silence.h"

const std::string silenceAbilityName = "Enchanted minion cannot use abilities";


Silence::Silence(int player) :
    Enchantment("Silence", 1, player, false, new Ability(),
                new Ability(false, silenceAbilityName, 0), new Ability(), new Ability(), new Ability(),
                "", "", false, true, true, true, true) { }

