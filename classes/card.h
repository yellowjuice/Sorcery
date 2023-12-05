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
        bool empty;
        std::string description;
        int cost;
      public:
        Ability(bool t, const std::string &desc, int cost) : 
            isTargetable{t}, empty{false}, 
            description{desc}, cost{cost} { }
        Ability(const std::string &desc) :
            isTargetable{false}, empty{true}, description{desc}, cost{0} { }
        Ability() : isTargetable{false}, empty{true}, 
                         description{""}, cost{0} { }
        virtual ~Ability() = default;

        virtual std::vector<Request> *get(int p, Location l, int i, int myP, Location myL, int myI); // generates a request

        bool targetable() const { return isTargetable; }
        virtual Card *getPtr(int p) const { return nullptr; }
        bool isEmpty() const { return empty; }
        std::string getDescription() const { return description; }
        int getCost() const { return cost; }

        virtual Ability *clone() {
            if (empty) return new Ability();
            return new Ability(isTargetable, description, cost);
        }
    };

  public:
    Card();
    Card(Type type, std::string name, int cost, int player);

    bool requestOwner(std::vector<Request> *v, Card *storage = nullptr);
    void notifyOwner(Notification n);

    // getters/setters
    Type getType() const;
    std::string getName() const;
    int getCost() const;
    int getPlayer() const;

    void setOwner(Observer *o);
    virtual card_template_t getAscii() const = 0;
    // do not use this to print more complicated structures
    friend std::ostream &operator<<(std::ostream &out, const Card &c); 
    
    virtual Card *clone() const = 0;
    Observer *getOwner() const;
};

#endif