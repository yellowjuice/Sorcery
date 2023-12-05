#include "../minion.h"
#ifndef BONEGOLEM_H
#define BONEGOLEM_H

extern const std::string boneGolemAbilityName;

class BoneGolem : public Minion {
    
    class BoneGolemAbility : public Ability {
      public:
        BoneGolemAbility();
        std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI) override;
        BoneGolemAbility *clone() override;
    };

  public:
    BoneGolem(int player);
};

#endif