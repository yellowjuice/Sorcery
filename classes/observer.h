#include <vector>
#ifndef OBSERVER_H
#define OBSERVER_H

enum Location { BOARD, DECK, GRAVEYARD, HAND, PLAYER, NONE };

class Card;

class Observer {
    Location location; // cards take the area they are in, others take their type

  public:
    struct Request {
        enum Command { 
            Add,        // target to location (target to board means play)
            Remove,     // target to card (process using location)
            Store,      // target to card (process using card)
            GetAction,  // target to minion/ritual (process using minion/ritual)
            Damage,     // target to minion (process using minion)
            Buff,       // target to minion (process using minion)
            Unenchant,  // target to minion (process using board)
            Attack,     // target to minion/player (process using minion/player)
            Retaliate,  // target to minion (process using minion)
            Play,       // target to card in hand (send from user)
            UseAbility, // target to minion (send from user) (process using board)
            UseAttack,  // target to minion (send from user) (process using board)
            Success,    // override output of request(...)
            Fail        // override output of request(...)
        };
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
        int arg; // uses: cmd=Attack/Retaliate/Buff, damage to deal or atk to increase
        
        // argument, only used for user input
        int arg_player;
        Location arg_location;
        int arg_index;
    };

    struct Notification {
        // start, end triggers send with player starting/ending turn
        // enter, exit triggers send with player minion belongs to
        enum Trigger { Start, End, Enter, Exit }; 

        Trigger trigger;
        int sender_player; // -1 if Start or End
        Location sender_location;
        int sender_index; // -1 unless enter or exit
        int arg; // player starting/ending if trigger is Start or End
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