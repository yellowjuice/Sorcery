#include "observer.h"
#include "minion.h"
#include "ritual.h"

#ifndef BOARD_H
#define BOARD_H

class Board : public Observer {
    std::vector<Minion *> minions;
    Ritual *ritual;
    Observer *owner;
    int player;
  public:
    Board(Observer *owner, int player);
    ~Board() override;

    bool request(std::vector<Request> *r, Card *c) override;
    bool notify(Notification n) override;

    card_template_t ritualAscii() const;
    friend std::ostream &operator<<(std::ostream &out, const Board &b);

    bool inspect(std::ostream &out, int i) const;
};

#endif