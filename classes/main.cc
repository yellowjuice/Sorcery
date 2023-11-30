#include "game.h"
#include <iostream>
#include <sstream>

const std::string helpMessage = "Commands: help -- Display this message.\nend -- End the current player's turn.\nquit -- End the game.\nattack minion other-minion -- Orders minion to attack other-minion.\nattack minion -- Orders minion to attack the opponent.\nplay card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\nuse minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\ninspect minion -- View a minion's card and all enchantments on that minion.\nhand -- Describe all cards in your hand.\nboard -- Describe all cards on the board.\n";

void printResult(bool x) {
    if (x) {
        std::cout << "call success" << std::endl;
    }
    else {
        std::cout << "call fail" << std::endl;
    }
}

int main() {
    Game *game = new Game("", "");
    std::string input = "";
    std::string cmd = "";
    char arg1 = ' ';
    char arg2 = ' ';
    char arg3 = ' ';
    while (getline(std::cin, input)) {
        std::istringstream iss(input);
        iss >> cmd;
        if (cmd == "end") {
            game->end();
        }
        else if (cmd == "quit") {
            break;
        }
        else if (cmd == "draw") { // only available in testing mode, change later
            game->draw();
        }
        else if (cmd == "discard") {
            iss >> arg1;
            if (!game->discard(int(arg1 - '1'))) {
                std::cout << "Discard failed" << std::endl;
            }
        }
        else if (cmd == "attack") {
            iss >> arg1;
            if (iss >> arg2) {
                if (!game->useAttack(int(arg1 - '1'), int(arg2 - '1'))) {
                    std::cout << "args were " << int(arg1 - '1') << ", " << int(arg2 - '1') << std::endl;
                    std::cout << "Attack failed" << std::endl;
                }
            }
            else {
                if (!game->useAttack(int(arg1 - '1'))) {
                    std::cout << "args were " << int(arg1 - '1') << std::endl;
                    std::cout << "Attack failed" << std::endl;
                }
            }
        }
        else if (cmd == "play") {
            iss >> arg1;
            if (iss >> arg2 >> arg3) {
                if (arg3 == 'r') arg3 = '6';
                if (!game->play(int(arg1 - '1'), int(arg2 - '0'), int(arg3 - '1'))) {
                    std::cout << "args were " << int(arg1 - '1') << ", " << int(arg2 - '0') << ", " << int(arg3 - '1') << std::endl;
                    std::cout << "Play failed" << std::endl;
                }
            }
            else {
                if (!game->play(int(arg1 - '1'))) {
                    std::cout << "args were " << int(arg1 - '1') << std::endl;
                    std::cout << "Play failed" << std::endl;
                }
            }
        }
        else if (cmd == "use") {
            iss >> arg1;
            if (iss >> arg2 >> arg3) {
                if (arg3 == 'r') arg3 = '6';
                if (!game->use(int(arg1 - '1'), int(arg2 - '0'), int(arg3 - '1'))) {
                    std::cout << "Use failed" << std::endl;
                }
            }
            else {
                if (!game->use(int(arg1 - '1'))) {
                    std::cout << "Use failed" << std::endl;
                }
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
    }

    delete game;

}