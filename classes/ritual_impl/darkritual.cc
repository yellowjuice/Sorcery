#include "darkritual.h"

const std::string darkRitualAbilityName = "At the start of your turn, gain 1 magic";

DarkRitual::DarkRitualAbility::DarkRitualAbility() :
    Ability(false, darkRitualAbilityName, 0) { }

std::vector<Observer::Request> *DarkRitual::DarkRitualAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (p == myP) retval->push_back(Request{myP, Location::PLAYER, myI, myP, myL, myI, Request::GetAction, 1});
    return retval;
}

DarkRitual::DarkRitualAbility *DarkRitual::DarkRitualAbility::clone() {
    return new DarkRitualAbility();
}

DarkRitual::DarkRitual(int player) :
    Ritual("Dark Ritual", 0, player, 5, 1, Notification::Trigger::Start, new DarkRitualAbility()) { }