#include "player.h"

Player::Player(Observer *owner, int p, std::string name) :
    owner{owner}, player{p}, board{new Board(this, p)}, hand{new Hand(this, p)}, 
    deck{new Deck(this, p)}, graveyard{new Graveyard(this, p)}, magic{3}, life{20}, name{name} {
        for (int i = 0; i < 5; ++i) {
            deck->draw();
        }
    }

Player::Player(Observer *owner, int p, std::string name, std::istream &in, bool testing) :
    owner{owner}, player{p}, board{new Board(this, p)}, hand{new Hand(this, p)}, 
    deck{new Deck(this, p, in, testing)}, graveyard{new Graveyard(this, p)}, magic{3}, life{20}, name{name} {
        for (int i = 0; i < 5; ++i) {
            deck->draw();
        }
    }

Player::~Player() {
    delete board;
    delete deck;
    delete hand;
    delete graveyard;
}

bool Player::request(std::vector<Request> *requests, Card *c) {
    if (requests->empty()) return true;
    Request r = (*requests)[0];
    if (r.target_player != player) return owner->request(requests, c);
    switch (r.target_location) {
        case Location::BOARD:
            return board->request(requests, c);
        case Location::HAND:
            return hand->request(requests, c);
        case Location::DECK:
            return deck->request(requests, c);
        case Location::GRAVEYARD:
            return graveyard->request(requests, c);
        case Location::NONE:
            return owner->request(requests, c);
        default:
        {
            switch(r.cmd) {
                case Request::Attack:
                    life -= r.arg;
                    break;
                    // later check if life < 0
                case Request::GetAction:
                    magic += r.arg;
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
    }
}

void Player::notify(Notification n) {
    if (n.trigger == Notification::Start && n.arg == player) {
        ++magic;
    }
    if (n.trigger == Notification::Start || n.trigger == Notification::End) {
        deck->notify(n);
        board->notify(n);
        hand->notify(n);
        graveyard->notify(n);
        return;
    }
    if (n.sender_player == player && n.sender_location != Location::NONE 
                                  && n.sender_location != Location::PLAYER) {
        owner->notify(n);
        return;
    }
    if (n.sender_player != player && n.sender_location != Location::NONE) {
        deck->notify(n);
        board->notify(n);
        hand->notify(n);
        graveyard->notify(n);
    }

}

void Player::print(std::ostream &out) const {
    std::vector<card_template_t> cardAscii;
    cardAscii.push_back(board->ritualAscii());
    cardAscii.push_back(CARD_TEMPLATE_EMPTY);
    cardAscii.push_back(display_player_card(player, name, life, magic));
    cardAscii.push_back(CARD_TEMPLATE_EMPTY);
    cardAscii.push_back(graveyard->getAscii());

    std::vector<card_template_t::iterator> iterators;
    for (auto &x : cardAscii) {
        iterators.push_back(x.begin());
    }

    if (player == 1) {
        out << EXTERNAL_BORDER_CHAR_TOP_LEFT << EXTERNAL_BORDER_TOP_BOTTOM;
        out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;
    }

    for ( ; iterators.at(0) != cardAscii[0].end() ; ) {
        out << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (auto &x : iterators) {
            out << (*x);
            ++x;
        }
        out << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }

    if (player == 2) {
        out << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT << EXTERNAL_BORDER_TOP_BOTTOM;
        out << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, const Player &p) {
    if (p.player == 1) {
        p.print(out);
        out << *(p.board);
        return out;
    }
    out << *(p.board);
    p.print(out);
    return out;
}

void Player::printHand(std::ostream &out) const {
    out << *hand;
}

bool Player::inspect(std::ostream &out, int i) const {
    return board->inspect(out, i);
}

int Player::numBoardCards() const {
    return board->numMinions();
}

int Player::numHandCards() const {
    return hand->numCards();
}

int Player::useCost(int i) const {
    return board->useCost(i);
}

int Player::playCost(int i) const {
    return hand->playCost(i);
}

int Player::getMagic() const {
    return magic;
}

void Player::useMagic(int i) {
    magic -= i;
    if (magic < 0) magic = 0;
}

int Player::getLife() const {
    return life;
}