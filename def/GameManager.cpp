//
// Created by svjat on 5/17/2025.
//

#include "../src/GameManager.h"

#include <iostream>

#include "../src/TitleState.h"
#include <SFML/Window.hpp>

GameManager::GameManager() {
    this->window.create(sf::VideoMode({850, 975}), "Minesweeper", sf::Style::Default);
    this->window.setFramerateLimit(30);

    running = true;
    ChangeState(new TitleState());
}

GameManager::~GameManager() {
    states.clear();
    this->window.close();
}

void GameManager::ChangeState(GameState* state) {
    if (!states.empty()) {
        delete states.back();
        states.pop_back();
    }
    states.push_back(state);
}

void GameManager::PushState(GameState* state) {
    states.back()->Pause();
    states.push_back(state);
}

void GameManager::PopState() {
    states.pop_back();
    states.back()->Resume();
}

void GameManager::HandleInput() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) { running = false; }
    }
    states.back()->HandleInput(this);
}

void GameManager::Update() {
    states.back()->Update(this);
}

void GameManager::Draw() {
    window.clear();
    states.back()->Draw(this);
    window.display();
}


