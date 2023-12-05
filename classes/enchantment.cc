#include "enchantment.h"

Enchantment::Enchantment(std::string name, int cost, int player, bool hasActive, Ability *active, 
                         Ability *start, Ability *end, Ability *enter, Ability *exit,
                         const std::string &atkText, const std::string &defText, bool hasStatM,
                         bool oStart, bool oEnd, bool oEnter, bool oExit, Ability *onPlay) :
    Card(Type::ENCHANTMENT, name, cost, player), hasActive{hasActive}, active{active}, 
    start{start}, end{end}, enter{enter}, exit{exit}, 
    oStart{oStart}, oEnd{oEnd}, oEnter{oEnter}, oExit{oExit},
    atkText{atkText}, defText{defText}, statM{hasStatM}, onPlay{onPlay} { }

Enchantment::~Enchantment() {
    delete active;
    delete start;
    delete end;
    delete enter;
    delete exit;
    delete onPlay;
}

int Enchantment::atkModifier(int x) { return x; }
int Enchantment::defModifier(int x) { return x; }
int Enchantment::activeCostModifier(int x) { return x; }

bool Enchantment::overrideActive() const { return hasActive; }
Card::Ability *Enchantment::getActive() { return active; }

bool Enchantment::overrideStart() const { return oStart; }
bool Enchantment::overrideEnd() const { return oEnd; }
bool Enchantment::overrideEnter() const { return oEnter; }
bool Enchantment::overrideExit() const { return oExit; }

Card::Ability *Enchantment::getStart() { return start; }
Card::Ability *Enchantment::getEnd() { return end;}
Card::Ability *Enchantment::getEnter() { return enter; }
Card::Ability *Enchantment::getExit() { return exit; }
Card::Ability *Enchantment::getOnPlay() { return onPlay; }

bool Enchantment::request(std::vector<Request> *v, Card *c) { 
    if (!v->empty() && (*v)[0].cmd == Request::Store) {
        v->erase(v->begin());
        return requestOwner(v, this);
    }
    return false;
}
void Enchantment::notify(Notification n) { }

card_template_t Enchantment::getAscii() const {
    if (statM) {
        if (hasActive) return display_enchantment_attack_defence(getName(), getCost(), 
                                                                 active->getDescription(),
                                                                 atkText, defText);
        if (!start->isEmpty()) return display_enchantment_attack_defence(getName(), getCost(), 
                                                                 start->getDescription(),
                                                                 atkText, defText);
        if (!end->isEmpty()) return display_enchantment_attack_defence(getName(), getCost(), 
                                                                 end->getDescription(),
                                                                 atkText, defText);
        if (!enter->isEmpty()) return display_enchantment_attack_defence(getName(), getCost(), 
                                                                 enter->getDescription(),
                                                                 atkText, defText);
        if (!exit->isEmpty()) return display_enchantment_attack_defence(getName(), getCost(), 
                                                                 exit->getDescription(),
                                                                 atkText, defText);
        return display_enchantment_attack_defence(getName(), getCost(), "", atkText, defText);
    }
    if (hasActive) return display_enchantment(getName(), getCost(), active->getDescription());
    if (!start->isEmpty()) return display_enchantment(getName(), getCost(), start->getDescription());
    if (!end->isEmpty()) return display_enchantment(getName(), getCost(), end->getDescription());
    if (!enter->isEmpty()) return display_enchantment(getName(), getCost(), enter->getDescription());
    if (!exit->isEmpty()) return display_enchantment(getName(), getCost(), exit->getDescription());
    return display_enchantment(getName(), getCost(), "");
}

Enchantment* Enchantment::clone() const {
    Enchantment *retval = new Enchantment(getName(), getCost(), getPlayer(), hasActive,
                                          active->clone(), start->clone(), end->clone(),
                                          enter->clone(), exit->clone(), atkText, defText, statM,
                                          oStart, oEnd, oEnter, oExit);
    retval->setLocation(getLocation());
    retval->setOwner(getOwner());
    return retval;
}