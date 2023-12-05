#include "minion.h"
#include "enchantedminion.h"

Minion::Minion(std::string name, int cost, int player, int attack, int defense, 
               Ability *active, Ability *start, Ability *end, Ability *enter, Ability *exit,
               int baseAttack, int baseDefense) :
    Card(Type::MINION, name, cost, player), attack{attack}, defense{defense}, actions{0}, 
    active{active}, start{start}, end{end}, enter{enter}, exit{exit}, index{-1}, 
    bAttack{baseAttack}, bDefense{baseDefense} { }

Minion::~Minion() {
    delete active;
    delete start;
    delete end;
    delete enter;
    delete exit;
}

int Minion::getAttack() const { return attack; }
int Minion::getDefense() const { return defense; }
int Minion::getActions() const { return actions; }

void Minion::addAction() { ++actions; }
void Minion::useAction() { if (actions > 0) --actions; }

bool Minion::attackPlayer() {
    if (actions <= 0) return false;
    std::vector<Request> *notifier = new std::vector<Request>;
    notifier->push_back(Request{(getPlayer() == 1) ? 2 : 1, Location::PLAYER, -1, 
                                getPlayer(), getLocation(), index, 
                                Request::Command::Attack, attack});
    bool retval = requestOwner(notifier, this);
    delete notifier;
    if (retval) --actions;
    return retval;
}
bool Minion::attackMinion(int i) {
    if (actions <= 0) return false;
    std::vector<Request> *notifier = new std::vector<Request>;
    notifier->push_back(Request{(getPlayer() == 1) ? 2 : 1, Location::BOARD, i,
                        getPlayer(), getLocation(), index, 
                        Request::Command::Attack, attack});
    bool retval = requestOwner(notifier, this);
    delete notifier;
    if (retval) --actions;
    return retval;
}

bool Minion::retaliate(Request r) {
    std::vector<Request> *notifier = new std::vector<Request>;
    notifier->push_back(Request{r.sender_player, r.sender_location, r.sender_index,
                        getPlayer(), getLocation(), index,
                        Request::Command::Retaliate, attack});
    bool retval = requestOwner(notifier, this);
    delete notifier;
    return retval;
}

bool Minion::isTargetable() const { return active->targetable(); }

bool Minion::useActive(int p, Location l, int i) {
    std::vector<Request> *notifier = active->get(p, l, i, getPlayer(), getLocation(), index);
    bool retval = requestOwner(notifier, active->getPtr(getPlayer()));
    delete notifier;
    return retval;
}
bool Minion::useStart(int p) {
    std::vector<Request> *notifier = start->get(p, Location::NONE, -1, getPlayer(), getLocation(), index);
    bool retval = requestOwner(notifier, start->getPtr(getPlayer()));
    delete notifier;
    return retval;
}
bool Minion::useEnd(int p) {
    std::vector<Request> *notifier = end->get(p, Location::NONE, -1, getPlayer(), getLocation(), index);
    bool retval = requestOwner(notifier, end->getPtr(getPlayer()));
    delete notifier;
    return retval;
}
bool Minion::useEnter(int p, Location l, int i) {
    std::vector<Request> *notifier = enter->get(p, l, i, getPlayer(), getLocation(), index);
    bool retval = requestOwner(notifier, enter->getPtr(getPlayer()));
    delete notifier;
    return retval;
}
bool Minion::useExit(int p, Location l, int i) {
    std::vector<Request> *notifier = exit->get(p, l, i, getPlayer(), getLocation(), index);
    bool retval = requestOwner(notifier, exit->getPtr(getPlayer()));
    delete notifier;
    return retval;
}

bool Minion::die() {
    std::vector<Request> *notifier = new std::vector<Request>;
    notifier->push_back(Request{getPlayer(), Location::BOARD, index,
                                getPlayer(), getLocation(), index,
                                Request::Command::Remove, 0});
    notifier->push_back(Request{getPlayer(), Location::GRAVEYARD, -1,
                                getPlayer(), getLocation(), index,
                                Request::Command::Add, 0});
    bool retval = requestOwner(notifier, this);
    delete notifier;
    return retval;
}

bool Minion::request(std::vector<Request> *v, Card *c) {
    if (!v->empty() && v->at(0).target_player == getPlayer()
           && v->at(0).target_location == getLocation() 
           && v->at(0).target_index == index) {
        switch(v->at(0).cmd) {
            case Request::Attack:
                loseDef(v->at(0).arg);
                retaliate(v->at(0));
                if (defense <= 0) die();
                break;
            case Request::Retaliate:
                loseDef(v->at(0).arg);
                if (defense <= 0) die();
                break;
            case Request::Damage:
                loseDef(v->at(0).arg);
                if (defense <= 0) die();
                break;
            case Request::Fail:
                return false;
            case Request::Success:
                v->erase(v->begin());
                requestOwner(v, c);
                return true;
            case Request::Store:
                c = this;
                break;
            case Request::Buff:
                addAtk(v->at(0).arg);
                break;
            case Request::GetAction:
                actions += v->at(0).arg;
                if (actions < 0) actions = 0;
                break;
            default:
                break;
        }
        v->erase(v->begin());
    }
    return requestOwner(v, c);
}

void Minion::notify(Notification n) {
    switch(n.trigger) {
        case Notification::Start:
            if (getActions() < 1 && n.arg == getPlayer()) addAction();
            useStart(n.arg);
            break;
        case Notification::End:
            useEnd(n.arg);
            break;
        case Notification::Enter:
            useEnter(n.sender_player, n.sender_location, n.sender_index);
            break;
        case Notification::Exit:
            useExit(n.sender_player, n.sender_location, n.sender_index);
            break;
        default:
            return;
    }
}

EnchantedMinion *Minion::enchant(Enchantment *e) {
    return new EnchantedMinion(this, e);
}

Minion *Minion::unenchant() {
    return this;
}

void Minion::setIndex(int i) {
    index = i;
}

int Minion::getIndex() const { return index; }

card_template_t Minion::getAscii() const {
    return getAsciiAlt(attack, defense);
}

card_template_t Minion::getAsciiAlt(int atk, int def) const {
    if (!active->isEmpty()) 
        return display_minion_activated_ability(getName(), getCost(), 
                                                atk, def, activeCost(), 
                                                active->getDescription());
    if (!start->isEmpty())
        return display_minion_triggered_ability(getName(), getCost(),
                                                atk, def, start->getDescription());
    if (!end->isEmpty())
        return display_minion_triggered_ability(getName(), getCost(),
                                                atk, def, end->getDescription());
    if (!enter->isEmpty())
        return display_minion_triggered_ability(getName(), getCost(),
                                                atk, def, enter->getDescription());
    if (!exit->isEmpty())
        return display_minion_triggered_ability(getName(), getCost(),
                                                atk, def, exit->getDescription());
    return display_minion_no_ability(getName(), getCost(), atk, def);
}

void Minion::inspectEnchants(std::ostream &out, std::vector<std::vector<card_template_t>> &v, int mod, bool print) const {

}

void Minion::inspectMe(std::ostream &out) const {
    card_template_t o = getAscii();
    for (auto x : o) {
        out << x << std::endl;
    }
}

void Minion::inspect(std::ostream &out) const {
    out << actions << " actions left" << std::endl;
    inspectMe(out);
    std::vector<std::vector<card_template_t>> temp;
    inspectEnchants(out, temp, 0, true);
}

bool Minion::hasActive() const {
    return !active->isEmpty();
}

int Minion::activeCost() const {
    return active->getCost();
}

Minion *Minion::clone() const {
    Minion *retval = new Minion(getName(), getCost(), getPlayer(), baseAttack(),
                                baseDefense(), active->clone(), start->clone(), end->clone(),
                                enter->clone(), exit->clone(), bAttack, bDefense);
    retval->setOwner(getOwner());
    retval->setIndex(getIndex());
    retval->setLocation(getLocation());
    return retval;
}

int Minion::baseAttack() const { return bAttack; }
int Minion::baseDefense() const { return bDefense; }

void Minion::setDefense(int d) { defense = d; }
void Minion::setAttack(int a) { attack = a; }

void Minion::addAtk(int n) { 
    attack += n;
}

void Minion::loseDef(int n) { 
    defense -= n;
}

