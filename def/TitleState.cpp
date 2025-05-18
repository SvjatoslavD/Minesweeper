//
// Created by svjat on 5/17/2025.
//

#include "../src/TitleState.h"
#include "../src/GameManager.h"
#include "../src/PlayingState.h"

#include <iostream>

TitleState::TitleState(GameManager* game) {
    //Creates background
    sf::RenderTexture rt({850, 975});
    rt.clear(mono_grey_dark);

    sf::Text text(*game->GetFont());
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setString("Minesweeper");
    text.setFillColor(mono_grey_medium);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    text.setOrigin({text.getGlobalBounds().getCenter()});
    text.setPosition({425,150});
    rt.draw(text);
    background_tex = rt.getTexture();

    //Create buttons
    Button *b1 = new Button(200, 300, 85, 450, "Easy", mono_grey_medium_light, mono_grey_light, game);
    buttons.push_back(b1);

    Button *b2 = new Button(200, 420, 85, 450, "Medium", mono_grey_medium_light, mono_grey_light, game);
    buttons.push_back(b2);

    Button *b3 = new Button(200, 540, 85, 450, "Hard", mono_grey_medium_light, mono_grey_light, game);
    buttons.push_back(b3);

    Button *b4 = new Button(250, 800, 75, 350, "Rules", mono_grey_medium_light, mono_grey_light, game);
    buttons.push_back(b4);
}

TitleState::~TitleState() {
    while (!buttons.empty()) {
        delete buttons.back();
        buttons.pop_back();
    }
}

void TitleState::HandleInput(GameManager* game) {
    if (!paused) {
        if (isKeyPressed(sf::Keyboard::Key::Escape)) {game->Quit();}
    }
}

void TitleState::Update(GameManager* game) {
    if (!paused && !buttons.empty()) {
        for (Button* button : buttons) {
            if (button->GetClicked(game)) {
                if (button->GetString() == "Easy") {
                    game->ChangeState(new PlayingState("Easy", game));
                    break;
                }
                else if (button->GetString() == "Medium") {
                    game->ChangeState(new PlayingState("Medium", game));
                    break;
                }
                else if (button->GetString() == "Hard") {
                    game->ChangeState(new PlayingState("Hard", game));
                    break;
                }
                // else if (button->GetString() == "Rules") {
                //     game->PushState(new RulesState());
                //     break;
                // }
            }
        }
    }
}
void TitleState::Draw(GameManager* game) {
    if (!paused) {
        sf::Sprite sprite(background_tex);
        //This is to make sure that the RenderTexture isn't displayed upside down
        sprite.setScale({1,-1});
        sprite.setPosition({0, 975});

        game->GetWindow()->draw(sprite);

        if (!buttons.empty()) {
            for (Button* button : buttons) {
                button->Draw(game);
            }
        }
    }
}