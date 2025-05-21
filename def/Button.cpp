//
// Created by svjat on 5/17/2025.
//

#include "../src/Button.h"

#include <iostream>

#include "../src/GameManager.h"
Button::Button(float x, float y, float h, float w, const std::string string, sf::Color standard, sf::Color hover, GameManager* game): text(*game->GetFont()) {
    info.setSize({w, h});
    info.setPosition({x, y});
    info.setFillColor(standard);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(1);
    this->standard = standard;
    this->hover = hover;
    text.setCharacterSize(h*3/5);
    text.setStyle(sf::Text::Bold);
    text.setString(string);
    text.setFillColor(mono_grey_medium);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setOrigin(text.getGlobalBounds().getCenter());
    text.setPosition(info.getPosition() + info.getSize()/2.f);
}

Button::~Button() {}

bool Button::GetContainsMouse(GameManager* game) {
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*game->GetWindow()));
    sf::Rect bounds = info.getGlobalBounds();

    if (bounds.contains(mousePos)) { return true; }
    else {return false;}
}

bool Button::GetClicked(GameManager* game) {
    if (GetContainsMouse(game) && isButtonPressed(sf::Mouse::Button::Left)) { return true; }
    else {return false;}
}

void Button::Draw(GameManager* game) {
    if (GetContainsMouse(game)) { info.setFillColor(hover); }
    else { info.setFillColor(standard); }

    game->GetWindow()->draw(info);
    game->GetWindow()->draw(text);
}

std::string Button::GetString() { return text.getString(); }
