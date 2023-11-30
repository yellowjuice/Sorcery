#include "airelemental.h"

AirElemental::AirElemental(int player) :
    Minion("Air Elemental", 0, player, 1, 1, Ability(player), 
    Ability(player), Ability(player), Ability(player), Ability(player)) { }