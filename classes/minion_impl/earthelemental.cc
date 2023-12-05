#include "earthelemental.h"

EarthElemental::EarthElemental(int player) :
    Minion("Earth Elemental", 3, player, 4, 4, new Ability(), 
    new Ability(), new Ability(), new Ability(), new Ability(), 4, 4) { }
