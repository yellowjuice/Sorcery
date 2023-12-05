#include "player.h"
#include <sstream>
#ifndef GAME_H
#define GAME_H

class Game : public Observer {
    Player *p1;
    Player *p2;
    int turn; // 1 or 2

  public:
    Game(std::string p1, std::string p2, std::istream &deck1, std::istream &deck2, bool testing);
    ~Game();

    bool draw();
    bool discard(int i);
    void end();

    bool useAttack(int i);
    bool useAttack(int i, int j);
    bool play(int i);
    bool play(int i, int p, int j);
    bool use(int i);
    bool use(int i, int p, int j);

    void printHand(int i, std::ostream &out) const;

    bool request(std::vector<Request> *requests, Card *c) override;
    void notify(Notification n) override;

    friend std::ostream &operator<<(std::ostream &out, const Game &g);

    bool inspect(std::ostream &out, int i) const;

    int getTurn() const;

    int numBoardCards() const;
    int numHandCards() const;
    int useCost(int i) const;
    int playCost(int i) const;

    int getMagic() const;
    void useMagic(int i);

    int getLife(int p) const;
};

#endif