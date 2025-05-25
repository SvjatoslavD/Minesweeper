//
// Created by svjat on 5/17/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Button.h"

class GameState {
public:
    virtual ~GameState() {};

    void Pause() { paused = true; };
    void Resume() { paused = false; };
    bool IsPaused() { return paused;}

    virtual void HandleInput(GameManager* game, sf::Event& event) {};
    virtual void Update(GameManager* game) {};
    virtual void Draw(GameManager* game) {};

protected:
    GameState() {};
    sf::Texture background_tex;
    std::vector<Button*> buttons;
    bool paused = false;
};



#endif //GAMESTATE_H
