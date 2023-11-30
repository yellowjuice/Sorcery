#include "card.h"
#ifndef DECK_H
#define DECK_H

class Deck : public Observer {
    std::vector<Card *> cards;
    Observer *owner;
    int player;

  public:
    Deck(Observer *owner, int player);
    ~Deck();

    void shuffle();

    bool request(std::vector<Request> *requests, Card *c);
    bool notify(Notification n);

    bool draw();
};

#endif