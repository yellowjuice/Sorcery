#include "novicepyromancer.h"

const std::string novicePyromancerAbilityName = "Deal 1 damage to target minion";

NovicePyromancer::NovicePyromancerAbility::NovicePyromancerAbility() :
    Ability(true, novicePyromancerAbilityName, 1) { }

std::vector<Observer::Request> *NovicePyromancer::NovicePyromancerAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Observer::Request>();
    retval->push_back(Request{p, l, i, myP, myL, myI, Request::Damage, 1});
    return retval;
}

NovicePyromancer::NovicePyromancer(int player) :
    Minion("Novice Pyromancer", 1, player, 0, 1, new NovicePyromancerAbility(), 
           new Ability(), new Ability(), new Ability(), new Ability(), 0, 1) { }

