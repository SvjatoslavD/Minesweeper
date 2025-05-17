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
    Button(float x, float y, float h, float w, const std::string& name, sf::Color standard, sf::Color hover);
    ~Button();

    bool ContainsMouse(GameManager* game);
    void Draw(GameManager* game);

protected:
    std::string name;
    sf::RectangleShape info;
    sf::Color standard;
    sf::Color hover;
};

#endif //BUTTON_H
