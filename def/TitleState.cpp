//
// Created by svjat on 5/17/2025.
//

#include "../src/TitleState.h"

#include <iostream>

#include "../src/GameManager.h"

TitleState::TitleState() {
    //Make background
    sf::RenderTexture rt({850, 975});
    rt.clear(mono_grey_dark);
    sf::RectangleShape bg(sf::Vector2f(100, 100));
    bg.setFillColor(sf::Color::Black);
    bg.setPosition(sf::Vector2f(300, 300));
    rt.draw(bg);
    bg.setFillColor(sf::Color::White);
    bg.setPosition(sf::Vector2f(300, 400));
    rt.draw(bg);
    background_tex = rt.getTexture();
    //Create buttons
}

TitleState::~TitleState() {
    buttons.clear();
}

void TitleState::Pause() {paused = true;}
void TitleState::Resume() {paused = false;}

void TitleState::HandleInput(GameManager* game) {
    if (!paused) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {game->Quit();}
    }
}

void TitleState::Update(GameManager* game) {
    if (!paused) {
        if (!buttons.empty()) {
            for (Button button : buttons) {
                button.ContainsMouse(game);
            }
        }
    }
}
void TitleState::Draw(GameManager* game) {
    if (!paused) {
        sf::Sprite sprite(background_tex);
        //This is to make sure that the RenderTexture isn't displayed upside down
        sprite.setScale({1,-1});
        sprite.setOrigin({0,975});
        sprite.setPosition(sf::Vector2f(0, 0));

        game->GetWindow()->draw(sprite);

        if (!buttons.empty()) {
            for (Button button : buttons) {
                button.Draw(game);
            }
        }
    }
}