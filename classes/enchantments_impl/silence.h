#include "../enchantment.h"
#ifndef SILENCE_H
#define SILENCE_H

extern const std::string silenceAbilityName;

class Silence : public Enchantment {

  public:
    Silence(int player);
};

#endif