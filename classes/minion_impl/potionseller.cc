#include "potionseller.h"

const std::string potionSellerAbilityName = "At the end of your turn, all your minions gain +0/+1.";

PotionSeller::PotionSellerAbility::PotionSellerAbility() :
    Ability(false, potionSellerAbilityName, 0) { }

std::vector<Observer::Request> *PotionSeller::PotionSellerAbility::get(int p, Location l, int i, int myP, Location myL, int myI) {
    std::vector<Request> *retval = new std::vector<Request>();
    if (p == myP) {
        retval->push_back(Request{myP, myL, 0, myP, myL, myI, Request::Damage, -1});
        retval->push_back(Request{myP, myL, 0, myP, myL, myI, Request::Success});
        for (int i = 1; i < 5; ++i) {
            retval->push_back(Request{myP, myL, i, myP, myL, myI, Request::Damage, -1});
        }
    }
    return retval;
}

PotionSeller::PotionSeller(int player) :
    Minion("Potion Seller", 2, player, 1, 3, new Ability(),
           new Ability(), new PotionSellerAbility(), new Ability(), new Ability(), 1, 3) { }

PotionSeller::PotionSellerAbility *PotionSeller::PotionSellerAbility::clone() {
    return new PotionSellerAbility();
}
