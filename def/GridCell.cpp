//
// Created by svjat on 5/18/2025.
//

#include "../src/GridCell.h"
#include "../src/GameManager.h"

GridCell::GridCell(float x, float y, float h, float w, sf::Color standard, sf::Color hover, GameManager* game): Button(x, y, h, w, "", standard, hover, game) {
    this->standard = standard;
    this->hover = hover;

    info.setSize({w, h});
    info.setPosition({x, y});
    info.setFillColor(standard);
    info.setOutlineColor(sf::Color::Black);
    info.setOutlineThickness(1);

    text.setCharacterSize(h*3/5);
    text.setString("");
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getLocalBounds().getCenter());
    text.setPosition(info.getPosition()+ sf::Vector2f{(float)(info.getSize().x/3.5), info.getSize().y/9});
}

GridCell::~GridCell() {}

void GridCell::GetMouseClick(GameManager* game, float timePassed) {
    if (timePassed < 500) {;}
    else {
        if (GetContainsMouse(game) && isButtonPressed(sf::Mouse::Button::Left)) {
            visible = 0;
            info.setFillColor(mono_grey_medium);
            text.setString(std::to_string(value));
        }
        else if (GetContainsMouse(game) && isButtonPressed(sf::Mouse::Button::Right)) {

        }
    }
}

bool GridCell::LostGame() {
    if (visible == 0 && value == -1) { return true; }
    else { return false; }
}

void GridCell::Draw(GameManager* game) {
    if (visible == 0) {;}
    else if (GetContainsMouse(game)) { info.setFillColor(hover); }
    else { info.setFillColor(standard); }

    game->GetWindow()->draw(info);
    game->GetWindow()->draw(text);
}