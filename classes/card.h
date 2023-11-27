#include "observer.h"
#include <string>
#include <vector>
#ifndef CARD_H
#define CARD_H

class Card : public Observer {
  public:
    enum Type { SPELL, MINION, ENCHANTMENT, RITUAL, NONE };

  private:
    Type type;
    std::string name;
    int cost;

    Observer *owner;
    int player;

  protected:
    class Ability {
        bool isTargetable;
        Card *defStorage;
      public:
        Ability(bool t, Card *d) : isTargetable{t}, defStorage{d} { }
        Ability() : isTargetable{false}, defStorage{nullptr} { }

        virtual std::vector<Request> *get(int p, Location l, int i) {
            return new std::vector<Request>; 
        } // generates a request

        bool targetable() const { return isTargetable; }
        Card *getPtr() const { return defStorage; }
        void setPtr(Card *d) { defStorage = d; }
    };

  public:
    Card();
    Card(Type type, std::string name, int cost, int player);
    virtual ~Card();

    bool requestOwner(std::vector<Request> *v, Card *storage = nullptr);
    bool notifyOwner(Notification n);

    // getters/setters
    Type getType() const;
    std::string getName() const;
    int getCost() const;
    int getPlayer() const;

    void setOwner(Observer *o);
    
};

#endif