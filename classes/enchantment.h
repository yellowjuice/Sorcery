#include "card.h"
#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

class Enchantment : public Card {
    bool hasActive;
    Ability *active;

    Ability *start;
    Ability *end;
    Ability *enter;
    Ability *exit;

    bool oStart;
    bool oEnd;
    bool oEnter;
    bool oExit;

    std::string atkText;
    std::string defText;
    bool statM;

    Ability *onPlay;
    
  public:
    Enchantment(std::string name, int cost, int player, bool hasActive, Ability *active, 
                Ability *start, Ability *end, Ability *enter, Ability *exit, 
                const std::string &atkText = "", const std::string &defText = "", bool hasStatM = false,
                bool oStart = false, bool oEnd = false, bool oEnter = false, bool oExit = false, 
                Ability *onPlay = new Ability());
    
    ~Enchantment() override;
    
    virtual int atkModifier(int x);
    virtual int defModifier(int x);
    virtual int activeCostModifier(int x);

    bool overrideActive() const;
    Ability *getActive();

    bool overrideStart() const;
    bool overrideEnd() const;
    bool overrideEnter() const;
    bool overrideExit() const;

    Ability *getStart();
    Ability *getEnd();
    Ability *getEnter();
    Ability *getExit();
    Ability *getOnPlay();
    

    bool request(std::vector<Request> *v, Card *storage) override;
    void notify(Notification n) override;

    card_template_t getAscii() const override;

    Enchantment *clone() const override;
};

#endif