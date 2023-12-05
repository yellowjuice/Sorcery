#include "auraofpower.h"

const std::string auraOfPowerAbilityName = "Whenever a minion enters play under your control, it gains +1/+1";

AuraOfPower::AuraOfPowerAbility::AuraOfPowerAbility() :
    Ability(false, auraOfPowerAbilityName, 0) { }

std::vector<Observer::Request> *AuraOfPower::AuraOfPowerAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (p == myP) {
        retval->push_back(Request{p, l, i, myP, myL, myI, Request::Damage, -1});
        retval->push_back(Request{p, l, i, myP, myL, myI, Request::Buff, 1});
    }
    return retval;
}

AuraOfPower::AuraOfPowerAbility *AuraOfPower::AuraOfPowerAbility::clone() {
    return new AuraOfPowerAbility();
}

AuraOfPower::AuraOfPower(int player) :
    Ritual("Aura of Power", 1, player, 4, 1, Notification::Trigger::Enter, new AuraOfPowerAbility()) { }