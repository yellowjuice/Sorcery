#include "airelemental.h"

AirElemental::AirElemental(int player) :
    Minion("Air Elemental", 0, player, 1, 1, new Ability(), 
    new Ability(), new Ability(), new Ability(), new Ability(), 1, 1) { }
