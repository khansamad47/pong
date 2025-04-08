#include <iostream>

#include "pong_game.h"

int main() {
    pong::Game game;

    if (game.initialize()) {
        game.runLoop();
    } else {
        std::cerr << "Game failed to initialized!\n";
    }
    game.stop();
    return 0;
}
