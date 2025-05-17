#include "src/GameManager.h"

int main() {
    GameManager game;

    while (game.Running()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }

    return 0;
}
