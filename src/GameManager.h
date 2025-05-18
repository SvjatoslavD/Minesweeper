//
// Created by svjat on 5/17/2025.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <vector>
#include <SFML/Graphics.hpp>

#include "ColorScheme.h"
#include "TitleState.h"

class GameState;

class GameManager {
public:

    GameManager();
    ~GameManager();

    void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState();

    void HandleInput();
    void Update();
    void Draw();

    bool Running() const {return running;}
    void Quit() {
        running = false;
    }

    sf::RenderWindow* GetWindow() {return &window;}
    sf::Font* GetFont() {return &font;}

private:
    sf::RenderWindow window;
    std::vector<GameState*> states;
    bool running;
    sf::Font font;
};

#endif //GAMEMANAGER_H
