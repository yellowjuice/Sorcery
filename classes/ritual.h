#include "card.h"

#ifndef RITUAL_H
#define RITUAL_H

class Ritual : public Card {
    int charges;
    int chargeCost;
    Notification::Trigger trigger;
    Ability passive;
    
  public:
    Ritual(std::string name, int cost, int player, int charges, 
            int chargeCost, Notification::Trigger trigger, Ability passive);
    
    bool request(std::vector<Request> *r, Card *c) override;
    bool notify(Notification n) override;
    
    card_template_t getAscii() const override;
};

#endif