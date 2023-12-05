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
    Player(Observer *owner, int player, std::string name, std::istream &in, bool testing);
    ~Player() override;

    bool request(std::vector<Request> *requests, Card *c) override;
    void notify(Notification n) override;

    friend std::ostream &operator<<(std::ostream &out, const Player &p);

    void printHand(std::ostream &out) const;

    bool inspect(std::ostream &out, int i) const;

    int numBoardCards() const;
    int numHandCards() const;

    int playCost(int i) const;
    int useCost(int i) const;

    int getMagic() const;
    void useMagic(int i);

    int getLife() const;
};

#endif