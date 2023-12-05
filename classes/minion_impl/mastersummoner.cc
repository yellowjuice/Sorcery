#include "mastersummoner.h"

const std::string masterSummonerAbilityName = "Summon up to three 1/1 air elementals";

MasterSummoner::MasterSummonerAbility::MasterSummonerAbility() :
    Ability(false, masterSummonerAbilityName, 2) { }

std::vector<Observer::Request> *MasterSummoner::MasterSummonerAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::IfFail, 1});
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Delete});
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Add});
    retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Success});
    for (int i = 0; i < 2; ++i) {
        retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Copy});
        retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::IfFail, 1});
        retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Delete});
        retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Add});
    }
    return retval;
}

AirElemental *MasterSummoner::MasterSummonerAbility::getPtr(int p) const {
    return new AirElemental(p);
}

MasterSummoner::MasterSummoner(int player) :
    Minion("Master Summoner", 3, player, 2, 3, new MasterSummonerAbility(),
           new Ability(), new Ability(), new Ability(), new Ability(), 2, 3) { }

MasterSummoner::MasterSummonerAbility *MasterSummoner::MasterSummonerAbility::clone() {
    return new MasterSummonerAbility();
}