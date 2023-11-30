#include "deck.h"
#include "minion_impl/airelemental.h"
#include "minion_impl/earthelemental.h"

Deck::Deck(Observer *owner, int player) :
    cards{std::vector<Card *>()}, owner{owner}, player{player} {
        for (int i = 0; i < 5; ++i) { 
            cards.push_back(new EarthElemental(player));
            cards.push_back(new AirElemental(player));
        }
        shuffle(); 
    }

Deck::~Deck() {
    while (!cards.empty()) {
        delete cards.back();
        cards.pop_back();
    }
}

void Deck::shuffle() { /*shuffle the cards*/ }

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
        default:
            return false;
    }
    requests->erase(requests->begin());
    return request(requests, c);
}

bool Deck::notify(Notification n) {
    if (n.trigger == Notification::Start && n.arg == player) {
        return draw();
    }
    return true;
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