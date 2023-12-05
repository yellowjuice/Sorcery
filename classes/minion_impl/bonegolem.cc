#include "bonegolem.h"

const std::string boneGolemAbilityName = "Gain +1/+1 whenever a minion leaves play.";

BoneGolem::BoneGolemAbility::BoneGolemAbility() :
    Ability(false, boneGolemAbilityName, 0) { }

BoneGolem::BoneGolem(int player) :
    Minion("Bone Golem", 2, player, 1, 3, new Ability(), 
           new Ability(), new Ability(), new Ability(), 
           new BoneGolemAbility(), 1, 3) { }

std::vector<Observer::Request> *BoneGolem::BoneGolemAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
            retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Buff, 1});
            retval->push_back(Request{myP, myL, myI, myP, myL, myI, Request::Damage, -1});
            return retval;
}

BoneGolem::BoneGolemAbility *BoneGolem::BoneGolemAbility::clone() {
    return new BoneGolemAbility();
}
