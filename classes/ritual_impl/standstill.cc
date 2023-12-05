#include "standstill.h"

const std::string standstillAbilityName = "Whenever a minion enters play, destroy it";

Standstill::StandstillAbility::StandstillAbility() :
    Ability(false, standstillAbilityName, 3) { }

std::vector<Observer::Request> *Standstill::StandstillAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{p, l, i, myP, myL, myI, Request::Store});
    retval->push_back(Request{p, Location::GRAVEYARD, i, myP, myL, myI, Request::Add});
    retval->push_back(Request{p, l, i, myP, myL, myI, Request::Remove});
    return retval;
}

Standstill::StandstillAbility *Standstill::StandstillAbility::clone() {
    return new StandstillAbility();
}

Standstill::Standstill(int player) :
    Ritual("Standstill", 3, player, 4, 2, Notification::Trigger::Enter, new StandstillAbility) { }