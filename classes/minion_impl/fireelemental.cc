#include "fireelemental.h"

const std::string fireElementalAbilityName = "Whenever an opponent's minion enter play, deal 1 damage to it.";

FireElemental::FireElementalAbility::FireElementalAbility() :
    Ability(false, fireElementalAbilityName, 0) { }

std::vector<Observer::Request> *FireElemental::FireElementalAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (p != myP) retval->push_back(Request{p, l, i, myP, myL, myI, Request::Damage, 1});
    return retval;
}

FireElemental::FireElemental(int player) :
    Minion("Fire Elemental", 2, player, 2, 2, new Ability(),
           new Ability(), new Ability(), new FireElementalAbility(), 
           new Ability(), 2, 2) { }

FireElemental::FireElementalAbility *FireElemental::FireElementalAbility::clone() {
    return new FireElementalAbility();
}