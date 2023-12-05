#include "disenchant.h"

const std::string disenchantAbilityName = "Destroy the top enchantment on target minion";

Disenchant::DisenchantAbility::DisenchantAbility() :
    Ability(true, disenchantAbilityName, 0) { }

std::vector<Observer::Request> *Disenchant::DisenchantAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (i >= 0 && i < 5) {
        retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Unenchant});
    }
    else retval->push_back(Request{p, Location::HAND, i, myP, myL, myI, Request::Fail});
    return retval;
}

Disenchant::Disenchant(int player) :
    Spell("Disenchant", 1, player, new DisenchantAbility()) { }