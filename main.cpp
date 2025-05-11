#include "src/BoardState.h"
#include "src/ColorScheme.h"
#include <SFML/Graphics.hpp>

const sf::Texture CreateScoreBoardTexture(int time_seconds, int mine_count);

int main() {
    BoardState bstate;

    bstate.TestViewBoard();

    sf::RenderWindow window(sf::VideoMode({850,975}), "Minesweeper", sf::Style::None);
    window.setFramerateLimit(30);

    float block_size = 50.f;

    sf::Texture texture3;

    sf::Clock clock;
    int game_state = 0;
    // 0 is titlescreen, 1 is gamerunning,2 is game over

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}
        }

            sf::Vector2 mouse_pos = sf::Mouse::getPosition(window);

            window.clear(mono_grey_dark);

            bstate.DrawGridTextureValues(&window, block_size, sf::Vector2f(mouse_pos)); // Also handles player input

            texture3 = CreateScoreBoardTexture(clock.getElapsedTime().asSeconds(), bstate.GetMineCount());
            sf::Sprite sprite3(texture3);
            sprite3.setPosition({25,850});
            window.draw(sprite3); // Scoreboard Texture

            window.display();


    }
}

const sf::Texture CreateGridTexture(float block_size) {
    sf::RenderTexture grid({800,800});
    grid.clear(sf::Color(0,0,0,0));

    sf::RectangleShape block({block_size,block_size});
    block.setFillColor(mono_grey_medium);
    block.setOutlineThickness(1.f);
    block.setOutlineColor(sf::Color(0,0,0,255));

    for (int i = 0; i < b_size; i++) {
        block.setPosition({static_cast<float>(i%row)*block_size,static_cast<float>(i/row)*block_size});
        grid.draw(block);
    }

    return grid.getTexture();
}

const sf::Texture CreateScoreBoardTexture(int time_seconds, int mine_count) {
    sf::RenderTexture grid({800,100});
    grid.clear(sf::Color(0,0,0,0));
    grid.setRepeated(false);

    sf::RectangleShape block2({800,100});
    block2.setPosition({0,0});
    block2.setFillColor(mono_grey_medium);
    block2.setOutlineThickness(1.f);
    block2.setOutlineColor(sf::Color(0,0,0,255));

    grid.draw(block2);

    sf::Font font = sf::Font("../assets/FiraCode-SemiBold.ttf");
    sf::Text text = sf::Text(font);
    text.setCharacterSize(60);
    text.setScale({1,-1});
    text.setFillColor(mono_grey_light);
    text.setString(std::to_string(time_seconds)+"s");
    text.setPosition({25,90});

    grid.draw(text);

    text.setFillColor(sf::Color::Black);
    text.setString(std::to_string(mine_count)+"M");
    text.setPosition({675,90});

    grid.draw(text);

    return grid.getTexture();
}
