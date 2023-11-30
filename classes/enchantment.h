#include "card.h"
#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

class Enchantment : public Card {
    bool hasActive;
    Ability active;

    Ability start;
    Ability end;
    Ability enter;
    Ability exit;

    bool oStart;
    bool oEnd;
    bool oEnter;
    bool oExit;

    std::string atkText;
    std::string defText;
    bool statM;
    
  public:
    Enchantment(std::string name, int cost, int player, bool hasActive, Ability active, 
                Ability start, Ability end, Ability enter, Ability exit,
                bool oStart = false, bool oEnd = false, bool oEnter = false, bool oExit = false,
                const std::string &atkText = "", const std::string &defText = "", bool hasStatM = false);
    
    virtual int atkModifier(int x);
    virtual int defModifier(int x);

    bool overrideActive() const;
    Ability &getActive();

    bool overrideStart() const;
    bool overrideEnd() const;
    bool overrideEnter() const;
    bool overrideExit() const;

    Ability &getStart();
    Ability &getEnd();
    Ability &getEnter();
    Ability &getExit();
    

    bool request(std::vector<Request> *v, Card *storage) override;
    bool notify(Notification n) override;

    card_template_t getAscii() const override;
};

#endif