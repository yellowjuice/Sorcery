#include "../minion.h"
#include "airelemental.h"
#ifndef APPRENTICESUMMONER_H
#define APPRENTICESUMMONER_H

extern const std::string apprenticeSummonerAbilityName;

class ApprenticeSummoner : public Minion {
    class ApprenticeSummonerAbility : public Ability {
      public:
        ApprenticeSummonerAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        AirElemental *getPtr(int p) const override;
        ApprenticeSummonerAbility *clone() override;
    };

  public:
    ApprenticeSummoner(int player);
};

#endif