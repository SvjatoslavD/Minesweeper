//
// Created by svjat on 5/17/2025.
//

#include "../src/PlayingState.h"

#include <iostream>

#include "../src/GameManager.h"
#include "../src/GridCell.h"

PlayingState::PlayingState(std::string diff, GameManager* game): diff(diff) {
    //Make background texture
    sf::RenderTexture rt({850,975});
    rt.clear(mono_grey_dark);

    sf::RectangleShape rect({800,100});
    rect.setFillColor(mono_grey_medium_light);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(1);
    rect.setPosition({25,850});
    rt.draw(rect);

    sf::Text text(*game->GetFont());
    text.setCharacterSize(50);
    text.setString(diff);
    text.setFillColor(mono_grey_medium);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setOrigin({text.getGlobalBounds().getCenter()});
    text.setPosition({425,900});

    rt.draw(text);

    background_tex = rt.getTexture();

    // Create Buttons
    Button *b1 = new Button(580, 870, 60, 225, "Rules", mono_grey_medium_light, mono_grey_light, game);
    buttons.push_back(b1);

    // Initialize variables
    if (diff == "Easy") {
        player_mine_count = 20;
        row = 10;
        col = 10;
        board_size = row * col;
        block_size = 800.f/ row;
    }
    else if (diff == "Medium") {
        player_mine_count = 35;
        row = 12;
        col = 12;
        board_size = row * col;
        block_size = 800.f/ row;
    }
    else if (diff == "Hard") {
        player_mine_count = 50;
        row = 15;
        col = 15;
        board_size = row * col;
        block_size = 800.f/ row;
    }

    // Creating the board
    PopulateGridCells(game);
}

PlayingState::~PlayingState() {
    while (!buttons.empty()) {
        delete buttons.back();
        buttons.pop_back();
    }
    while (!grid_cells.empty()) {
        delete grid_cells.back();
        grid_cells.pop_back();
    }
}

void PlayingState::HandleInput(GameManager* game) {
    if (!paused) {
        if (isKeyPressed(sf::Keyboard::Key::Escape)) {game->Quit();}
    }
}

void PlayingState::Update(GameManager* game) {
    if (!paused && !buttons.empty()) {
        for (Button* button : buttons) {
            ;
        }
        for (GridCell* grid_cell : grid_cells) {
            grid_cell->GetMouseClick(game, clock.getElapsedTime().asMilliseconds());
        }
    }
}

void PlayingState::Draw(GameManager* game) {
    if (!paused) {
        sf::Sprite sprite(background_tex);
        //This is to make sure that the RenderTexture isn't displayed upside down
        sprite.setScale({1,-1});
        sprite.setPosition({0, 975});
        game->GetWindow()->draw(sprite);

        UpdateScoreBoard(game);
        sf::Sprite sprite2(score_board_tex);
        sprite2.setScale({1,-1});
        sprite2.setPosition({25, 950});
        game->GetWindow()->draw(sprite2);

        if (!buttons.empty()) {
            for (Button* button : buttons) {
                button->Draw(game);
            }
        }

        if (!grid_cells.empty()) {
            for (GridCell* cell : grid_cells) {
                cell->Draw(game);
            }
        }
    }
}

void PlayingState::UpdateScoreBoard(GameManager* game) {
    sf::RenderTexture rt({800,100});
    rt.clear(sf::Color(0,0,0,0));

    sf::Text text{*game->GetFont()};
    text.setString(std::to_string(int(clock.getElapsedTime().asSeconds()))+"s");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setOrigin({20,25});
    text.setPosition({50,45});

    rt.draw(text);

    text.setString(std::to_string(player_mine_count)+"M");
    text.setFillColor(sf::Color::Black);
    text.setOutlineThickness(0);
    text.setOrigin({0,25});
    text.setPosition({180,45});

    rt.draw(text);

    score_board_tex = rt.getTexture();
}

void PlayingState::PopulateGridCells(GameManager* game) {
    int offset = 25;
    for (int i = 0; i < board_size; i++) {
        auto *gc = new GridCell((i % row) * block_size + offset, (i / col) * block_size + offset, block_size, block_size, mono_grey_medium_light, mono_grey_light, game);
        grid_cells.push_back(gc);
    }
}