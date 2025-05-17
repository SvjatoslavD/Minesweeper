//
// Created by svjat on 5/17/2025.
//

#include "../src/Button.h"
#include "../src/GameManager.h"

Button::Button(float x, float y, float h, float w, const std::string& name, sf::Color standard, sf::Color hover) {
    info.setSize({h,w});
    info.setPosition({x,y});
    info.setFillColor(standard);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(1);
}

Button::~Button() {}

bool Button::ContainsMouse(GameManager* game) {
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*game->GetWindow()));
    sf::Rect bounds = info.getLocalBounds();

    if (bounds.contains(mousePos)) { return true; }
    else {return false;}
}

void Button::Draw(GameManager* game) {
    game->GetWindow()->draw(info);
}