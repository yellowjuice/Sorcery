#include "card.h"
#ifndef HAND_H
#define HAND_H

class Hand : public Observer {
    std::vector<Card *> cards;
    Observer *owner;
    int player;
  
  public:
    Hand(Observer *owner, int player);
    ~Hand() override;

    int numCards() const;
    bool request(std::vector<Request> *requests, Card *c) override;
    void notify(Notification n) override;

    friend std::ostream &operator<<(std::ostream &out, const Hand &h);

    int playCost(int i) const;
};

#endif