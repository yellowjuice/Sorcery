#include "unsummon.h"

const std::string unsummonAbilityName = "Return target minion to its owner's hand";

Unsummon::UnsummonAbility::UnsummonAbility() :
    Ability(true, unsummonAbilityName, 0) { }

std::vector<Observer::Request> *Unsummon::UnsummonAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (i >= 0 && i < 5) {
        retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Store});
        retval->push_back(Request{p, Location::HAND, i, myP, myL, myI, Request::Add});
        retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Remove});
    }
    else retval->push_back(Request{p, Location::HAND, i, myP, myL, myI, Request::Fail});
    return retval;
}

Unsummon::Unsummon(int player) :
    Spell("Unsummon", 2, player, new UnsummonAbility()) { }