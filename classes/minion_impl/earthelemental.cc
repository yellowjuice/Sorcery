#include "earthelemental.h"

EarthElemental::EarthElemental(int player) :
    Minion("Earth Elemental", 0, player, 4, 4, Ability(player), 
    Ability(player), Ability(player), Ability(player), Ability(player)) { }