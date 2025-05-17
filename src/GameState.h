//
// Created by svjat on 5/17/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Button.h"

class GameState {
public:
    GameState() {};
    virtual ~GameState() {};

    virtual void Pause() {};
    virtual void Resume() {};

    virtual void HandleInput(GameManager* game) {};
    virtual void Update(GameManager* game) {};
    virtual void Draw(GameManager* game) {};

protected:
    sf::Texture background_tex;
    std::vector<Button> buttons;
    bool paused = false;
};



#endif //GAMESTATE_H
