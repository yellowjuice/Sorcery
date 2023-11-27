#include <vector>
#ifndef OBSERVER_H
#define OBSERVER_H

enum Location { BOARD, DECK, GRAVEYARD, HAND, PLAYER, NONE };

class Card;

class Observer {
    Location location; // cards take the area they are in, others take their type

  public:
    struct Request {
        enum Command { Add, Remove, GiveAction, Damage, Buff, Attack, Retaliate, Play, Store, Fail };
        // target location
        int target_player; // 1 for p1, 2 for p2, 0 otherwise
        Location target_location;
        int target_index; // 0 - 4 for minions, 5 for ritual, -1 for none
        
        //sender location
        int sender_player;
        Location sender_location;
        int sender_index;

        //instructions
        Command cmd;
        int arg;
    };

    struct Notification {
        // start, end triggers send with player starting/ending turn
        // enter, exit triggers send with player minion belongs to
        enum Trigger { Start, End, Enter, Exit }; 

        Trigger trigger;
        int sender_player;
        Location sender_location;
        int sender_index; // -1 unless enter or exit
    };

    Observer();
    Observer(Location l);
    virtual ~Observer();

    virtual bool request(std::vector<Request> *m, Card *storage) = 0;
    virtual bool notify(Notification n) = 0;

    Location getLocation() const;
    void setLocation(Location l);
};

#endif