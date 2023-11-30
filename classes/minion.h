#include "card.h"
#include "enchantment.h"
#include <iostream>
#ifndef MINION_H
#define MINION_H

class EnchantedMinion;

class Minion : public Card {
    int attack;
    int defense;
    int actions;
    
    Ability active;
    Ability start;
    Ability end;
    Ability enter;
    Ability exit;
    int index;

  protected:
    virtual void inspectEnchants(std::ostream &out, std::vector<std::vector<card_template_t>> &v, int mod, bool print = false) const;
    

  public:
    
    Minion();
    Minion(std::string name, int cost, int player, int attack, int defense, 
           Ability active, Ability start, Ability end, Ability enter, Ability exit);
    
    int getAttack() const;
    int getDefense() const;
    int getActions() const;

    void addAction();
    void useAction();
    bool attackPlayer();
    bool attackMinion(int i);
    bool retaliate(Request r);

    virtual bool isTargetable() const;

    virtual bool useActive(int p = 0, Location l = Location::NONE, int i = -1);
    virtual bool useStart(int p);
    virtual bool useEnd(int p);
    virtual bool useEnter(int p, Location l, int i);
    virtual bool useExit(int p, Location l, int i);

    bool die();
    
    bool request(std::vector<Request> *v, Card *c) override;
    bool notify(Notification n) override; // do not call this

    EnchantedMinion *enchant(Enchantment *e);
    virtual Minion *unenchant();

    void setIndex(int i);
    int getIndex() const;

    card_template_t getAscii() const override;
    
    void inspect(std::ostream &out) const;
};

#endif