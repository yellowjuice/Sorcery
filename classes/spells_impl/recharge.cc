#include "recharge.h"

const std::string rechargeAbilityName = "Your ritual gains 3 charges";

Recharge::RechargeAbility::RechargeAbility() :
    Ability(false, rechargeAbilityName, 0) { }

std::vector<Observer::Request> *Recharge::RechargeAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, Location::BOARD, 5, myP, myL, myI, Request::GetAction, 3});
    return retval;
}

Recharge::Recharge(int player) :
    Spell("Recharge", 1, player, new RechargeAbility()) { }