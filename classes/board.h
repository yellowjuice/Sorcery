#include "observer.h"
#include "minion.h"
#include "ritual.h"

#ifndef BOARD_H
#define BOARD_H

class Board : public Observer {
    Card *cards[5];
    Ritual *ritual;
    Observer *owner;
    int player;
  public:
    Board(Observer *owner, int player);
    ~Board() override;

    bool request(std::vector<Request> *r, Card *c) override;
    bool notify(Notification n) override;

};

#endif