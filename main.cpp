#include "src/BoardState.h"
#include "src/ColorScheme.h"
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({850,975}), "Minesweeper", sf::Style::Default);
    window.setFramerateLimit(30);

    BoardState bstate(&window);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}
        }

        bstate.HandleInput();

        bstate.ProcessGame();

        window.clear(mono_grey_dark); // This is always the background

        bstate.RenderGame();

        window.display();
    }
}


