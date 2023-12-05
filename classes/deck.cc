#include <cstdlib>
#include <ctime>
#include "deck.h"
#include "minion_impl/airelemental.h"
#include "minion_impl/earthelemental.h"
#include "minion_impl/bonegolem.h"
#include "minion_impl/fireelemental.h"
#include "minion_impl/potionseller.h"
#include "minion_impl/novicepyromancer.h"
#include "minion_impl/mastersummoner.h"
#include "minion_impl/apprenticesummoner.h"
#include "ritual_impl/darkritual.h"
#include "ritual_impl/auraofpower.h"
#include "ritual_impl/standstill.h"
#include "spells_impl/banish.h"
#include "spells_impl/unsummon.h"
#include "spells_impl/recharge.h"
#include "spells_impl/disenchant.h"
#include "spells_impl/raisedead.h"
#include "spells_impl/blizzard.h"
#include "enchantments_impl/giantstrength.h"
#include "enchantments_impl/enrage.h"
#include "enchantments_impl/haste.h"
#include "enchantments_impl/magicfatigue.h"
#include "enchantments_impl/silence.h"


Deck::Deck(Observer *owner, int player) :
    cards{std::vector<Card *>()}, owner{owner}, player{player} {
        cards.push_back(new AirElemental(player));
        cards.push_back(new EarthElemental(player));
        cards.push_back(new FireElemental(player));
        cards.push_back(new PotionSeller(player));
        cards.push_back(new NovicePyromancer(player));
        cards.push_back(new ApprenticeSummoner(player));
        cards.push_back(new MasterSummoner(player));
        cards.push_back(new Banish(player));
        cards.push_back(new Unsummon(player));
        cards.push_back(new Recharge(player));
        cards.push_back(new Disenchant(player));
        cards.push_back(new RaiseDead(player));
        cards.push_back(new Blizzard(player));
        cards.push_back(new GiantStrength(player));
        cards.push_back(new MagicFatigue(player));
        cards.push_back(new Silence(player));
        cards.push_back(new DarkRitual(player));
        cards.push_back(new AuraOfPower(player));
        cards.push_back(new Standstill(player));
        shuffle(); 
    }

Deck::Deck(Observer *owner, int player, std::istream &in, bool testing) :
    cards{std::vector<Card *>()}, owner{owner}, player{player} {
        std::string s = "";
        while (getline(in, s)) {
            if (s == "Air Elemental") cards.push_back(new AirElemental(player));
            else if (s == "Earth Elemental") cards.push_back(new EarthElemental(player));
            else if (s == "Fire Elemental") cards.push_back(new FireElemental(player));
            else if (s == "Potion Seller") cards.push_back(new PotionSeller(player));
            else if (s == "Novice Pyromancer") cards.push_back(new NovicePyromancer(player));
            else if (s == "Apprentice Summoner") cards.push_back(new ApprenticeSummoner(player));
            else if (s == "Master Summoner") cards.push_back(new MasterSummoner(player));
            else if (s == "Banish") cards.push_back(new Banish(player));
            else if (s == "Unsummon") cards.push_back(new Unsummon(player));
            else if (s == "Recharge") cards.push_back(new Recharge(player));
            else if (s == "Disenchant") cards.push_back(new Disenchant(player));
            else if (s == "Raise Dead") cards.push_back(new RaiseDead(player));
            else if (s == "Blizzard") cards.push_back(new Blizzard(player));
            else if (s == "Giant Strength") cards.push_back(new GiantStrength(player));
            else if (s == "Magic Fatigue") cards.push_back(new MagicFatigue(player));
            else if (s == "Silence") cards.push_back(new Silence(player));
            else if (s == "Dark Ritual") cards.push_back(new DarkRitual(player));
            else if (s == "Aura of Power") cards.push_back(new AuraOfPower(player));
            else if (s == "Standstill") cards.push_back(new Standstill(player));
            else if (s == "Enrage") cards.push_back(new Enrage(player));
            else if (s == "Haste") cards.push_back(new Haste(player));
            else if (s == "Bone Golem") cards.push_back(new BoneGolem(player));
            else std::cout << "Invalid card" << std::endl;
        }
        if (!testing) {
            shuffle();
        }
    }


Deck::~Deck() {
    while (!cards.empty()) {
        delete cards.back();
        cards.pop_back();
    }
}

void Deck::shuffle() {
    for (size_t i = 0; i < cards.size(); ++i) {
        size_t x = rand() % cards.size();
        Card *temp = cards[i];
        cards[i] = cards[x];
        cards[x] = temp;
    }
}

bool Deck::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player != player) return owner->request(requests, c);
    if (r.target_location != Location::DECK) return owner->request(requests, c);
    switch(r.cmd) {
        case Request::Add:
            // not sure if this will ever be used, modify to random if used
            if (c == nullptr) return false;
            cards.push_back(c);
            break;
        case Request::Remove: // client can only remove top
            cards.pop_back();
            break;
        case Request::Store: // client can only access top
            c = cards.back();
            break;
        case Request::Success:
            requests->erase(requests->begin());
            request(requests, c);
            return true;
        case Request::Fail:
            return false;
        case Request::Copy:
            c = c->clone();
            break;
        case Request::Delete:
            delete c;
            break;
        case Request::IfFail:
            {
            requests->erase(requests->begin());
            if (requests->empty()) return true;
            std::vector<Request> temp;
            for (int j = 0; j < r.arg && !requests->empty(); ++j) {
                temp.push_back((*requests)[0]);
                requests->erase(requests->begin());
            }
            bool v = request(requests, c);
            if (!v) {
                request(&temp, c);
                return false;
            }
            return true;
            }
        default:
            return false;
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

void Deck::notify(Notification n) {
    if (n.trigger == Notification::Start && n.arg == player) {
        draw();
    }
}

bool Deck::draw() {
    if (!cards.empty()) {
        std::vector<Request> notifier;
        notifier.push_back(Request{player, Location::HAND, -1,
                                   player, Location::DECK, -1,
                                   Request::Add});
        if (owner->request(&notifier, cards.back())) {
            cards.pop_back();
        }
        else return false;
    }
    return true;
}