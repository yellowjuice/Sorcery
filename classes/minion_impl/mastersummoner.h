#include "../minion.h"
#include "airelemental.h"
#ifndef MASTERSUMMONER_H
#define MASTERSUMMONER_H

extern const std::string masterSummonerAbilityName;

class MasterSummoner : public Minion {

    class MasterSummonerAbility : public Ability {
      public:
        MasterSummonerAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        AirElemental *getPtr(int p) const override;
        MasterSummonerAbility *clone() override;
    };

  public:
    MasterSummoner(int player);

};

#endif