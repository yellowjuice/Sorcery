#include "raisedead.h"

const std::string raiseDeadAbilityName = "Resurrect the top minion in your graveyard and set its defence to 1";

RaiseDead::RaiseDeadAbility::RaiseDeadAbility() :
    Ability(false, raiseDeadAbilityName, 0) { }

std::vector<Observer::Request> *RaiseDead::RaiseDeadAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, Location::GRAVEYARD, -1, myP, myL, myI, Request::Store});
    retval->push_back(Request{myP, Location::BOARD, -1, myP, myL, myI, Request::Add});
    retval->push_back(Request{myP, Location::GRAVEYARD, -1, myP, myL, myI, Request::Remove, 1});
    return retval;
}

RaiseDead::RaiseDead(int player) :
    Spell("Raise Dead", 1, player, new RaiseDeadAbility()) { }