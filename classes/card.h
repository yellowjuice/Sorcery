#include "observer.h"
#include "asciiart/ascii_graphics.h"
#include <iostream>
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
        int player;
        bool empty;
        std::string description;
        int cost;
      public:
        Ability(bool t, Card *d, int p, const std::string &desc, int cost) : isTargetable{t}, defStorage{d}, 
                                                                   player{p}, empty{false}, 
                                                                   description{desc}, cost{cost} { }
        Ability(int p) : isTargetable{false}, defStorage{nullptr}, player{p}, 
                         empty{true}, description{""}, cost{0} { }

        virtual std::vector<Request> *get(int p, Location l, int i) {
            return new std::vector<Request>; 
        } // generates a request

        bool targetable() const { return isTargetable; }
        Card *getPtr() const { return defStorage; }
        void setPtr(Card *d) { defStorage = d; }
        bool isEmpty() const { return empty; }
        std::string getDescription() const { return description; }
        int getCost() const { return cost; }
    };

  public:
    Card();
    Card(Type type, std::string name, int cost, int player);

    bool requestOwner(std::vector<Request> *v, Card *storage = nullptr);
    bool notifyOwner(Notification n);

    // getters/setters
    Type getType() const;
    std::string getName() const;
    int getCost() const;
    int getPlayer() const;

    void setOwner(Observer *o);
    virtual card_template_t getAscii() const = 0;
    // do not use this to print more complicated structures
    friend std::ostream &operator<<(std::ostream &out, const Card &c); 
    
};

#endif