#include "game.h"

Game::Game(std::string name1, std::string name2, std::istream &deck1, std::istream &deck2, bool testing) :
    p1{new Player(this, 1, name1, deck1, testing)}, 
    p2{new Player(this, 2, name2, deck2, testing)}, 
    turn{1} { }

Game::~Game() {
    delete p1;
    delete p2;
}

bool Game::draw() {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::DECK, -1,
                               -1, Location::NONE, -1,
                               Request::Store});
    notifier.push_back(Request{turn, Location::DECK, -1,
                               -1, Location::NONE, -1,
                               Request::Remove});
    notifier.push_back(Request{turn, Location::HAND, -1,
                               -1, Location::NONE, -1,
                               Request::Add});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::discard(int i) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::HAND, i,
                               -1, Location::NONE, -1,
                               Request::Store});
    notifier.push_back(Request{turn, Location::HAND, i,
                               -1, Location::NONE, -1,
                               Request::Remove});
    Card *c = nullptr;
    bool out = false;
    if (turn == 1) out = p1->request(&notifier, c);
    else out = p2->request(&notifier, c);
    if (!out) return false;
    delete c;
    return true;
}

void Game::end() {
    if (turn == 1) {
        p1->notify(Notification{Notification::End, -1, Location::NONE, -1, turn});
        p2->notify(Notification{Notification::End, -1, Location::NONE, -1, turn});
        turn = 2;
        p2->notify(Notification{Notification::Start, -1, Location::NONE, -1, turn});
        p1->notify(Notification{Notification::Start, -1, Location::NONE, -1, turn});
    }
    else {
        p2->notify(Notification{Notification::End, -1, Location::NONE, -1, turn});
        p1->notify(Notification{Notification::End, -1, Location::NONE, -1, turn});
        turn = 1;
        p1->notify(Notification{Notification::Start, -1, Location::NONE, -1, turn});
        p2->notify(Notification{Notification::Start, -1, Location::NONE, -1, turn});
    }
}

bool Game::useAttack(int i) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::BOARD, i,
                               -1, Location::NONE, -1,
                               Request::UseAttack, 0,
                               3 - turn, Location::PLAYER, -1});
    bool out = false;
    if (turn == 1) out = p1->request(&notifier, nullptr);
    else out = p2->request(&notifier, nullptr);
    return out;
}

bool Game::useAttack(int i, int j) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::BOARD, i,
                               -1, Location::NONE, -1,
                               Request::UseAttack, 0,
                               3 - turn, Location::BOARD, j});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::play(int i) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::HAND, i,
                               -1, Location::NONE, -1,
                               Request::Play, 0,
                               turn, Location::BOARD, -1});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::play(int i, int p, int j) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::HAND, i,
                               -1, Location::NONE, -1,
                               Request::Play, 0,
                               p, Location::BOARD, j});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::use(int i) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::BOARD, i,
                               -1, Location::NONE, -1,
                               Request::UseAbility, 0,
                               turn, Location::BOARD, -1});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::use(int i, int p, int j) {
    std::vector<Request> notifier;
    notifier.push_back(Request{turn, Location::BOARD, i,
                               -1, Location::NONE, -1,
                               Request::UseAbility, 0,
                               p, Location::BOARD, j});
    if (turn == 1) return p1->request(&notifier, nullptr);
    else return p2->request(&notifier, nullptr);
}

bool Game::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player == 1) return p1->request(requests, c);
    else if (r.target_player == 2) return p2->request(requests, c);
    return false; // might change later to account for losing
}

void Game::notify(Notification n) {
    if (n.sender_player == 1) p2->notify(n);
    else if (n.sender_player == 2) p1->notify(n);
}

std::ostream &operator<<(std::ostream &out, const Game &g) {
    out << *(g.p1);
    for (auto &x : CENTRE_GRAPHIC) {
        out << x;
        out << std::endl;
    }
    out << *(g.p2);
    return out;
}

void Game::printHand(int i, std::ostream &out) const {
    if (i == 1) p1->printHand(out);
    if (i == 2) p2->printHand(out);
}

bool Game::inspect(std::ostream &out, int i) const {
    if (turn == 1) return p1->inspect(out, i);
    if (turn == 2) return p2->inspect(out, i);
    return false;
}

int Game::getTurn() const { return turn; }

int Game::numBoardCards() const {
    if (turn == 1) return p1->numBoardCards();
    return p2->numBoardCards();
}

int Game::numHandCards() const {
    if (turn == 1) return p1->numHandCards();
    return p2->numHandCards();
}

int Game::playCost(int i) const {
    if (turn == 1) return p1->playCost(i);
    return p2->playCost(i);
}

int Game::useCost(int i) const {
    if (turn == 1) return p1->useCost(i);
    return p2->useCost(i);
}

int Game::getMagic() const {
    if (turn == 1) return p1->getMagic();
    return p2->getMagic();
}

void Game::useMagic(int i) {
    if (turn == 1) p1->useMagic(i);
    else p2->useMagic(i);
}

int Game::getLife(int p) const {
    if (p == 1) return p1->getLife();
    return p2->getLife();
}