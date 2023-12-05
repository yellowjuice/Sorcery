#include "apprenticesummoner.h"

const std::string apprenticeSummonerAbilityName = "Summon a 1/1 air elemental";

ApprenticeSummoner::ApprenticeSummonerAbility::ApprenticeSummonerAbility() :
    Ability(false, apprenticeSummonerAbilityName, 1) { }

std::vector<Observer::Request> *ApprenticeSummoner::ApprenticeSummonerAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::IfFail, 1});
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Delete});
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Add});
    return retval;
}

ApprenticeSummoner::ApprenticeSummonerAbility *ApprenticeSummoner::ApprenticeSummonerAbility::clone() {
    return new ApprenticeSummonerAbility();
}

AirElemental *ApprenticeSummoner::ApprenticeSummonerAbility::getPtr(int p) const {
    return new AirElemental(p);
}

ApprenticeSummoner::ApprenticeSummoner(int player) :
    Minion("Apprentice Summoner", 1, player, 1, 1, new ApprenticeSummonerAbility(),
           new Ability(), new Ability(), new Ability(), new Ability(), 1, 1) { }
