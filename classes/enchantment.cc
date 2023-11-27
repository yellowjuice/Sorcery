#include "enchantment.h"

Enchantment::Enchantment() :
    Card(Type::ENCHANTMENT, "", 0, 0), hasActive{false}, start{Ability()}, 
    end{Ability()}, enter{Ability()}, exit{Ability()} { }

Enchantment::Enchantment(std::string name, int cost, int player, bool hasActive, Ability active, 
                         Ability start, Ability end, Ability enter, Ability exit,
                         bool oStart, bool oEnd, bool oEnter, bool oExit) :
    Card(Type::ENCHANTMENT, name, cost, player), hasActive{hasActive}, active{active}, 
    start{start}, end{end}, enter{enter}, exit{exit}, 
    oStart{oStart}, oEnd{oEnd}, oEnter{oEnter}, oExit{oExit} { }

int Enchantment::atkModifier(int x) { return x; }
int Enchantment::defModifier(int x) { return x; }

bool Enchantment::overrideActive() const { return hasActive; }
Card::Ability &Enchantment::getActive() { return active; }

bool Enchantment::overrideStart() const { return oStart; }
bool Enchantment::overrideEnd() const { return oEnd; }
bool Enchantment::overrideEnter() const { return oEnter; }
bool Enchantment::overrideExit() const { return oExit; }

Card::Ability &Enchantment::getStart() { return start; }
Card::Ability &Enchantment::getEnd() { return end;}
Card::Ability &Enchantment::getEnter() { return enter; }
Card::Ability &Enchantment::getExit() { return exit; }

bool Enchantment::request(std::vector<Request> *v, Card *c) { return true; }
bool Enchantment::notify(Notification n) { return true; }