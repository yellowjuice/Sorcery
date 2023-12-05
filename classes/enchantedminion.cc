#include "enchantedminion.h"

EnchantedMinion::EnchantedMinion(Minion *m, Enchantment *e) :
        Minion(m->getName(), m->getCost(), m->getPlayer(), e->atkModifier(m->getAttack()), 
               e->defModifier(m->getDefense()), new Ability(), new Ability(), 
               new Ability(), new Ability(), new Ability(), m->baseAttack(), m->baseDefense()), m{m}, e{e} {
            setLocation(m->getLocation());
            setIndex(m->getIndex());
            setOwner(m->getOwner());
            while (m->getActions() > 0 && this->getActions() < m->getActions()) {
                addAction();
            }
        }

EnchantedMinion::~EnchantedMinion() {
    delete e;
}

bool EnchantedMinion::useActive(int p, Location l, int i) {
    if (getActions() <= 0) return false;
    if (e->overrideActive()) {
        std::vector<Request> *notifier = e->getActive()->get(p, l, i, getPlayer(), getLocation(), getIndex());
        bool retval = m->requestOwner(notifier, e->getActive()->getPtr(e->getPlayer()));
        delete notifier;
        if (retval) useAction();
        return retval;
    }
    return m->useActive();
}

bool EnchantedMinion::useStart(int p) {
    if (e->overrideStart()) {
        std::vector<Request> *notifier = e->getStart()->get(p, Location::NONE, -1, getPlayer(), getLocation(), getIndex());
        bool retval = m->requestOwner(notifier, e->getStart()->getPtr(e->getPlayer()));
        delete notifier;        
        return retval;
    }
    bool retval = m->useStart(p);
    if (retval) {
        std::vector<Request> *notifier = e->getStart()->get(p, Location::NONE, -1, getPlayer(), getLocation(), getIndex());
        retval = m->requestOwner(notifier, e->getStart()->getPtr(e->getPlayer()));
        delete notifier;        
    }
    return retval;
}

bool EnchantedMinion::useEnd(int p) {
    if (e->overrideEnd()) {
        std::vector<Request> *notifier = e->getEnd()->get(p, Location::NONE, -1, getPlayer(), getLocation(), getIndex());
        bool retval = m->requestOwner(notifier, e->getEnd()->getPtr(e->getPlayer()));
        delete notifier;        
        return retval;
    }
    bool retval = m->useEnd(p);
    if (retval) {
        std::vector<Request> *notifier = e->getEnd()->get(p, Location::NONE, -1, getPlayer(), getLocation(), getIndex());
        retval = m->requestOwner(notifier, e->getEnd()->getPtr(e->getPlayer()));
        delete notifier;        
    }
    return retval;
}

bool EnchantedMinion::useEnter(int p, Location l, int i) {
    if (e->overrideEnter()) {
        std::vector<Request> *notifier = e->getEnter()->get(p, l, i, getPlayer(), getLocation(), getIndex());
        bool retval = m->requestOwner(notifier, e->getEnter()->getPtr(e->getPlayer()));
        delete notifier;        
        return retval;
    }
    bool retval = m->useEnter(p, l, i);
    if (retval) {
        std::vector<Request> *notifier = e->getEnter()->get(p, l, i, getPlayer(), getLocation(), getIndex());
        retval = m->requestOwner(notifier, e->getEnter()->getPtr(e->getPlayer()));
        delete notifier;        
    }
    return retval;
}
bool EnchantedMinion::useExit(int p, Location l, int i) {
    if (e->overrideEnter()) {
        std::vector<Request> *notifier = e->getExit()->get(p, l, i, getPlayer(), getLocation(), getIndex());
        bool retval = m->requestOwner(notifier, e->getExit()->getPtr(e->getPlayer()));
        delete notifier;        
        return retval;
    }
    bool retval = m->useExit(p, l, i);
    if (retval) {
        std::vector<Request> *notifier = e->getExit()->get(p, l, i, getPlayer(), getLocation(), getIndex());
        retval = m->requestOwner(notifier, e->getExit()->getPtr(e->getPlayer()));
        delete notifier;        
    }
    return retval;
}

Minion *EnchantedMinion::unenchant() {
    return m;
}

void EnchantedMinion::inspectMe(std::ostream &out) const {
    card_template_t o = getAsciiAlt(getAttack(), getDefense());
    for (auto x : o) {
        out << x << std::endl;
    }
}

void EnchantedMinion::inspectEnchants(std::ostream &out, std::vector<std::vector<card_template_t>> &v, int mod, bool print) const {
    if (mod % 5 == 0) {
        v.insert(v.begin(), std::vector<card_template_t>());
        mod = 0;
    }
    v[0].insert(v[0].begin(), e->getAscii());
    m->inspectEnchants(out, v, mod + 1, false);
    if (print) {
        for (std::vector<card_template_t> &x : v) {
            std::vector<card_template_t::iterator> its;
            for (card_template_t &y : x) {
                its.push_back(y.begin());
            }
            for ( ; its[0] != x[0].end() ; ) {
                for (card_template_t::iterator &z : its) {
                    out << *z;
                    ++z;
                }
                out << std::endl;
            }
        }
    }
}

bool EnchantedMinion::hasActive() const {
    if (e->overrideActive()) {
        return !e->getActive()->isEmpty();
    }
    return m->hasActive();
}

int EnchantedMinion::activeCost() const {
    return e->activeCostModifier(m->activeCost());
}

Minion *EnchantedMinion::clone() const {
    return m->clone();
}

void EnchantedMinion::addAtk(int n) {
    setAttack(getAttack() + n);
    m->addAtk(n);
}

void EnchantedMinion::loseDef(int n) {
    setDefense(getDefense() - n);
    m->loseDef(n);
}

card_template_t EnchantedMinion::getAsciiAlt(int atk, int def) const {
    return m->getAsciiAlt(atk, def);
}