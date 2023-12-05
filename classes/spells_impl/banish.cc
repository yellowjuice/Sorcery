#include "banish.h"

const std::string banishAbilityName = "Destroy target minion or ritual";

Banish::BanishAbility::BanishAbility() :
    Ability(true, banishAbilityName, 0) { }

std::vector<Observer::Request> *Banish::BanishAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (i >= 0 && i < 5) {
        retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Store});
        retval->push_back(Request{p, Location::GRAVEYARD, i, myP, myL, myI, Request::Add});
    }
    if (i >= 0 && i <= 5) retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Remove});
    else retval->push_back(Request{p, Location::BOARD, i, myP, myL, myI, Request::Fail});
    return retval;
}

Banish::Banish(int player) :
    Spell("Banish", 2, player, new BanishAbility()) { }