#include "game.h"
#include <iostream>
#include <sstream>
#include <fstream>

const std::string helpMessage = "Commands: help -- Display this message.\nend -- End the current player's turn.\nquit -- End the game.\nattack minion other-minion -- Orders minion to attack other-minion.\nattack minion -- Orders minion to attack the opponent.\nplay card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\nuse minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\ninspect minion -- View a minion's card and all enchantments on that minion.\nhand -- Describe all cards in your hand.\nboard -- Describe all cards on the board.\n";
bool testing = false;
bool init = false;
Game *game;
int namesGotten = 0;
std::string deck1File = "default.deck";
std::string deck2File = "default.deck";
std::string initFile = "";
std::string p1, p2 = "";

enum ProcessState { DECK1, DECK2, INIT, OTHER };

void processCommand(std::string &s, bool &cont) {
    char arg1 = ' ';
    char arg2 = ' ';
    char arg3 = ' ';
    std::string cmd = "";
    std::istringstream iss(s);
    iss >> cmd;
    if (cmd == "end") {
        game->end();
    }
    else if (cmd == "help") {
        std::cout << helpMessage;
    }
    else if (cmd == "quit") {
        cont = false;
        return;
    }
    else if (cmd == "draw" && testing) {
        game->draw();
    }
    else if (cmd == "discard" && testing) {
        iss >> arg1;
        if (!game->discard(int(arg1 - '1'))) {
            std::cout << "Discard failed" << std::endl;
        }
    }
    else if (cmd == "attack") {
        iss >> arg1;
        if (iss >> arg2) {
            if (!game->useAttack(int(arg1 - '1'), int(arg2 - '1'))) {
                std::cout << "Attack failed" << std::endl;
            }
        }
        else {
            if (!game->useAttack(int(arg1 - '1'))) {
                std::cout << "Attack failed" << std::endl;
            }
        }
    }
    else if (cmd == "play") {
        iss >> arg1;
        int index = int(arg1 - '1');
        if (index < game->numHandCards() && index >= 0 && 
            (testing || game->getMagic() >= game->playCost(index))) {
            int cost = game->playCost(index);
            if (iss >> arg2 >> arg3) {
                if (arg3 == 'r') arg3 = '6';
                if (!game->play(index, int(arg2 - '0'), int(arg3 - '1'))) {
                    std::cout << "Play failed" << std::endl;
                }
                else {
                    game->useMagic(cost);
                }
            }
            else {
                if (!game->play(index)) {
                    std::cout << "Play failed" << std::endl;
                }
                else {
                    game->useMagic(cost);
                }
            }
        }
        else {
            if (index >= game->numHandCards()) std::cout << "invalid index" << std::endl;
            else if (index < 0)  std::cout << "invalid index" << std::endl;
            else if (game->getMagic() < game->playCost(index)) std::cout << "not enough magic" << std::endl;
        }
    }
    else if (cmd == "use") {
        iss >> arg1;
        int index = int(arg1 - '1');
        if (index < game->numBoardCards() && index >= 0 && 
            (testing || game->getMagic() >= game->useCost(index))) {
            int cost = game->useCost(index);
            if (iss >> arg2 >> arg3) {
                if (arg3 == 'r') arg3 = '6';
                if (!game->use(index, int(arg2 - '0'), int(arg3 - '1'))) {
                    std::cout << "Use failed" << std::endl;
                }
                else {
                    game->useMagic(cost);
                }
            }
            else {
                if (!game->use(index)) {
                    std::cout << "Use failed" << std::endl;
                }
                else {
                    game->useMagic(cost);
                }
            }
        }
        else {
            if (index >= game->numBoardCards()) std::cout << "invalid index" << std::endl;
            else if (index < 0)  std::cout << "invalid index" << std::endl;
            else if (game->getMagic() < game->useCost(index)) std::cout << "not enough magic" << std::endl;
        }
    }
    else if (cmd == "inspect") {
        iss >> arg1;
        if (!game->inspect(std::cout, int(arg1 - '1'))) {
            std::cout << "Inspect failed" << std::endl;
        }
    }
    else if (cmd == "hand") {
        game->printHand(game->getTurn(), std::cout);
    }
    else if (cmd == "board") {
        std::cout << *game;
    }
    else {
        std::cout << "Not a valid command" << std::endl;
    }
    if (game->getLife(1) <= 0) {
        std::cout << "Player 2 wins" << std::endl;
        cont = false;
    }
    else if (game->getLife(2) <= 0) {
        std::cout << "Player 1 wins" << std::endl;
        cont = false;
    }
}

void processInput(std::istream &in) {
    std::string s = "";
    while (getline(in, s)) {
        if (namesGotten == 2 && game == nullptr) {
            std::ifstream f1(deck1File);
            std::ifstream f2(deck2File);
            game = new Game(p1, p2, f1, f2, testing);
        }
        if (namesGotten == 0) {
            p1 = s;
            ++namesGotten;
        }
        else if (namesGotten == 1) {
            p2 = s;
            ++namesGotten;
        }
        else {
            bool cont = true;
            processCommand(s, cont);
            if (!cont) break;
        }
        
    }
}

void processArgs(int argc, char *argv[]) {
    ProcessState p = OTHER;
    for (int i = 1; i < argc; ++i) {
        std::ostringstream o;
        o << argv[i];
        std::string curArg = o.str();
        switch(p) {
            case OTHER:
                if (curArg == "-deck1") {
                    p = DECK1;
                    break;
                }
                if (curArg == "-deck2") {
                    p = DECK2;
                    break;
                }
                if (curArg == "-init") {
                    p = INIT;
                    init = true;
                    break;
                }
                if (curArg == "-testing") {
                    testing = true;
                    break;
                }
                break;
            case DECK1:
                deck1File = curArg;
                p = OTHER;
                break;
            case DECK2:
                deck2File = curArg;
                p = OTHER;
                break;
            case INIT:
                initFile = curArg;
                p = OTHER;
                break;
        }
    }
    if (init) {
        std::ifstream f(initFile);
        processInput(f);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    processArgs(argc, argv);
    if (namesGotten == 0) {
        std::cout << "Enter player 1 name: ";
        getline(std::cin, p1);
        ++namesGotten;
    }
    if (namesGotten == 1) {
        std::cout << "Enter player 2 name: ";
        getline(std::cin, p2);
        ++namesGotten;
    }
    if (namesGotten == 2 && game == nullptr) {
        std::ifstream f1(deck1File);
        std::ifstream f2(deck2File);
        game = new Game(p1, p2, f1, f2, testing);
    }

    processInput(std::cin);
    delete game;
}