#include "board.h"
#include "deck.h"
#include "hand.h"
#include "graveyard.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public Observer {
    Observer *owner;
    int player;
    Board *board;
    Hand *hand;
    Deck *deck;
    Graveyard *graveyard;
    int magic;
    int life;

    std::string name;

    void print(std::ostream &out) const;

  public:
    Player(Observer *owner, int player, std::string name);
    ~Player() override;

    bool request(std::vector<Request> *requests, Card *c) override;
    bool notify(Notification n);

    friend std::ostream &operator<<(std::ostream &out, const Player &p);

    void printHand(std::ostream &out) const;

    bool inspect(std::ostream &out, int i) const;
};

#endif