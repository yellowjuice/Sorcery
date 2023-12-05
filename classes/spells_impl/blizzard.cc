#include "blizzard.h"

const std::string blizzardAbilityName = "Deal 2 damage to all minions";

Blizzard::BlizzardAbility::BlizzardAbility() :
    Ability(false, blizzardAbilityName, 0) { }

std::vector<Observer::Request> *Blizzard::BlizzardAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, Location::BOARD, 6, myP, myL, myI, Request::Damage, 2});
    retval->push_back(Request{3 - myP, Location::BOARD, 6, myP, myL, myI, Request::Damage, 2});
    return retval;
}

Blizzard::Blizzard(int player) :
    Spell("Blizzard", 3, player, new BlizzardAbility()) { }