#include "haste.h"

const std::string hasteAbilityName = "Enchanted minion gains +1 action per turn";

Haste::HasteAbilityStart::HasteAbilityStart() :
    Ability(false, hasteAbilityName, 0) { }

std::vector<Observer::Request> *Haste::HasteAbilityStart::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::GetAction, 1});
    return retval;
}

Haste::HasteAbilityEnd::HasteAbilityEnd() :
    Ability(false, hasteAbilityName, 0) { }

std::vector<Observer::Request> *Haste::HasteAbilityEnd::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::GetAction, -1});
    return retval;
}

Haste::HasteAbilityOnPlay::HasteAbilityOnPlay() :
    Ability(false, hasteAbilityName, 0) { }

std::vector<Observer::Request> *Haste::HasteAbilityOnPlay::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::GetAction, 1});
    return retval;
}

Haste::Haste(int player) :
    Enchantment("Haste", 1, player, false, new Ability(),
                new HasteAbilityStart(), new HasteAbilityEnd(), new Ability(), new Ability(),
                "", "", false, false, false, false, false, new HasteAbilityOnPlay()) { }