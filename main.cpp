#include "src/BoardState.h"
#include <SFML/Graphics.hpp>

int main() {
    BoardState bstate;

    bstate.TestViewHalfBoard();
    bstate.PrintBoardVisible();

    sf::RenderWindow window(sf::VideoMode({800,600}), "Minesweeper");
    window.setFramerateLimit(30);

    while (window.isOpen()) {
        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {window.close();}

            window.clear(sf::Color::Green);
            window.display();
        }
    }
}
