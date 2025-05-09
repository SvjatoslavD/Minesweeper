#include "src/BoardState.h"
#include "src/ColorScheme.h"
#include <SFML/Graphics.hpp>

const sf::Texture CreateGridTexture(float block_size);

int main() {
    BoardState bstate;

    bstate.TestViewBoard();
    std::cout << bstate.GetMineCount() << " ";

    sf::RenderWindow window(sf::VideoMode({850,950}), "Minesweeper");
    window.setFramerateLimit(30);

    float block_size = 50.f;

    sf::Texture texture = CreateGridTexture(block_size);
    sf::Texture texture2;
    sf::Sprite sprite(texture);
    sf::Sprite sprite2(texture);
    sprite.setPosition({25,25});
    sprite2.setPosition({25,25});

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}

            window.clear(mono_grey_dark);
            window.draw(sprite);
            texture2 = bstate.CreateGridTextureValues(block_size);
            sprite2.setTexture(texture2);
            window.draw(sprite2);
            window.display();
        }
    }
}

const sf::Texture CreateGridTexture(float block_size) {
    sf::RenderTexture grid({800,800});
    grid.clear();

    sf::RectangleShape block({block_size,block_size});
    block.setPosition({0,0});
    block.setFillColor(mono_grey_medium);
    block.setOutlineThickness(1.f);
    block.setOutlineColor(sf::Color(0,0,0,255));

    for (int i = 0; i < b_size; i++) {
        block.setPosition({static_cast<float>(i/row)*block_size,static_cast<float>(i%row)*block_size});
        grid.draw(block);
    }

    return grid.getTexture();
}
