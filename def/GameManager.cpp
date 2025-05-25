//
// Created by svjat on 5/17/2025.
//

#include "../src/GameManager.h"

#include <iostream>

#include "../src/TitleState.h"
#include <SFML/Window.hpp>

GameManager::GameManager() {
    window.create(sf::VideoMode({850, 975}), "Minesweeper", sf::Style::Default);
    window.setPosition({500, 0});
    window.setFramerateLimit(30);

    running = true;

    font = sf::Font("../assets/FiraCode-SemiBold.ttf");

    ChangeState(new TitleState(this));
}

GameManager::~GameManager() {
    while (!states.empty()) {
        delete states.back();
        states.pop_back();
    }
    window.close();
}

void GameManager::ChangeState(GameState* state) {
    if (!states.empty()) {
        delete states.back();
        states.pop_back();
    }
    states.push_back(state);
}

void GameManager::PushState(GameState* state) {
    if (!states.empty()) {
        states.back()->Pause();
    }
    states.push_back(state);
}

void GameManager::PopState() {
    if (!states.empty()) {
        delete states.back();
        states.pop_back();
        states.back()->Resume();
    }
    else {
        std::cerr << "No state to pop" << std::endl;
    }
}

void GameManager::HandleInput() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) { running = false; }

        states.back()->HandleInput(this, *event);
    }
}

void GameManager::Update() {
    states.back()->Update(this);
}

void GameManager::Draw() {
    window.clear();
    states.back()->Draw(this);
    window.display();
}


