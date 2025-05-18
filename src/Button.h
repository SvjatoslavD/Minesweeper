//
// Created by svjat on 5/17/2025.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

class GameManager;

class Button {
public:
    Button(float x, float y, float h, float w, std::string string, sf::Color standard, sf::Color hover, GameManager* game);
    ~Button();

    bool GetContainsMouse(GameManager* game);
    bool GetClicked(GameManager* game);
    void Draw(GameManager* game);
    std::string GetString();

protected:
    sf::Text text;
    sf::RectangleShape info;
    sf::Color standard;
    sf::Color hover;
};

#endif //BUTTON_H
