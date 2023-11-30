#include "enchantedminion.h"

EnchantedMinion::EnchantedMinion(Minion *m, Enchantment *e) :
        Minion(m->getName(), m->getCost(), m->getPlayer(), e->atkModifier(m->getAttack()), 
               e->defModifier(m->getDefense()), Ability(m->getPlayer()), Ability(m->getPlayer()), 
               Ability(m->getPlayer()), Ability(m->getPlayer()), Ability(m->getPlayer())) {
            setLocation(m->getLocation());
            setIndex(m->getIndex());
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
        std::vector<Request> *notifier = e->getActive().get(p, l, i);
        bool retval = m->requestOwner(notifier, e->getActive().getPtr());
        delete notifier;
        if (retval) useAction();
        return retval;
    }
    return m->useActive();
}

bool EnchantedMinion::useStart(int p) {
    if (e->overrideStart()) {
        std::vector<Request> *notifier = e->getStart().get(p, Location::NONE, -1);
        bool retval = m->requestOwner(notifier, e->getStart().getPtr());
        delete notifier;        
        return retval;
    }
    bool retval = m->useStart(p);
    if (retval) {
        std::vector<Request> *notifier = e->getStart().get(p, Location::NONE, -1);
        retval = m->requestOwner(notifier, e->getStart().getPtr());
        delete notifier;        
    }
    return retval;
}

bool EnchantedMinion::useEnd(int p) {
    if (e->overrideEnd()) {
        std::vector<Request> *notifier = e->getEnd().get(p, Location::NONE, -1);
        bool retval = m->requestOwner(notifier, e->getEnd().getPtr());
        delete notifier;        
        return retval;
    }
    bool retval = m->useEnd(p);
    if (retval) {
        std::vector<Request> *notifier = e->getEnd().get(p, Location::NONE, -1);
        retval = m->requestOwner(notifier, e->getEnd().getPtr());
        delete notifier;        
    }
    return retval;
}

bool EnchantedMinion::useEnter(int p, Location l, int i) {
    if (e->overrideEnter()) {
        std::vector<Request> *notifier = e->getEnter().get(p, l, i);
        bool retval = m->requestOwner(notifier, e->getEnter().getPtr());
        delete notifier;        
        return retval;
    }
    bool retval = m->useEnter(p, l, i);
    if (retval) {
        std::vector<Request> *notifier = e->getEnter().get(p, l, i);
        retval = m->requestOwner(notifier, e->getEnter().getPtr());
        delete notifier;        
    }
    return retval;
}

bool EnchantedMinion::useExit(int p, Location l, int i) {
    if (e->overrideEnter()) {
        std::vector<Request> *notifier = e->getExit().get(p, l, i);
        bool retval = m->requestOwner(notifier, e->getExit().getPtr());
        delete notifier;        
        return retval;
    }
    bool retval = m->useExit(p, l, i);
    if (retval) {
        std::vector<Request> *notifier = e->getExit().get(p, l, i);
        retval = m->requestOwner(notifier, e->getExit().getPtr());
        delete notifier;        
    }
    return retval;
}

Minion *EnchantedMinion::unenchant() {
    return m;
}

void EnchantedMinion::inspectEnchants(std::ostream &out, std::vector<std::vector<card_template_t>> &v, int mod, bool print) const {
    if (mod % 5 == 0) {
        v.insert(v.begin(), std::vector<card_template_t>());
        mod = 0;
    }
    v[0].insert(v[0].begin(), e->getAscii());
    inspectEnchants(out, v, mod + 1, false);
    if (print) {
        for (std::vector<card_template_t> &x : v) {
            std::vector<card_template_t::iterator> its;
            for (card_template_t &y : x) {
                its.push_back(y.begin());
            }
            for ( ; its[0] != x[0].end() ; ) {
                for (auto &z : its) {
                    out << *z;
                }
                out << std::endl;
            }
        }
    }
}