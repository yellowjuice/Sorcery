#include "observer.h"
#include "minion.h"
#ifndef GRAVEYARD_H
#define GRAVEYARD_H

class Graveyard : public Observer {
    std::vector<Minion *> minions;
    Observer *owner;
    int player;

  public:
    Graveyard(Observer *owner, int player);
    ~Graveyard() override;

    Minion *getTop();

    bool request(std::vector<Request> *requests, Card *c) override;
    bool notify(Notification n);
    card_template_t getAscii() const;

};

#endif