//
// Created by svjat on 5/8/2025.
//
#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "ColorScheme.h"



class StateManager {
public:
    StateManager(sf::RenderWindow* render_window) {
        window = render_window;

        row = 9;
        col = 9;
        b_size = row*col;
        block_size = 800/col;

        max_mine_count = 10;

        PopulateMines();
        CalculateValuesOnGrid();
        TestViewBoard();
    };

    ~StateManager() {};

    void HandleInput() {
        HandleKeyboard();
    }

    void ProcessGame() {
        // CheckButtons();
        // CheckGridCells();
    }

    void RenderGame() {
        switch (game_state) {
            case 0:
                DrawTitleScreen();
                game_state = 1;
                break;
            case 1:
                DrawGridTextureValues();
                DrawScoreBoard();
                break;
            case 2:
                DrawGameOverScreen();
                break;
        }

    }

    void TestPrintBoardValues() const {
        for (int i = 0; i < b_size; i++) {
            std::cout << board_val[i] << " ";
            if ((i+1)%row == 0) { std::cout << "\n"; }
        }
    };

    void TestPrintBoardVisible() const {
        for (int i = 0; i < b_size; i++) {
            if (board_visible[i] == 0) { std::cout << "x" << " "; }
            else { std::cout << board_val[i] << " "; }

            if ((i+1)%row == 0) { std::cout << "\n"; }
        }
    }

    void TestViewBoard() {
        for (int i = 0; i < b_size/2; i++) {
            board_visible[i] = 1;
        }
    }

private:
    float first_click = true;
    int game_state = 0;

    int row;
    int col;
    int b_size;
    float block_size;

    std::vector<int> board_val{};
    std::vector<int> board_visible{};

    int mine_count = 0;
    int max_mine_count;

    sf::RenderWindow* window;
    sf::Clock clock;

    sf::Font font = sf::Font("../assets/FiraCode-SemiBold.ttf");
    sf::Text text = sf::Text(font);

    void DrawTitleScreen() {}
    void DrawGameOverScreen() {}

    void DrawGridTextureValues() {
        text.setCharacterSize(block_size*3/5);

        int offset = 25;

        for (int i = 0; i < b_size; i++) {
            if (board_visible[i] == 1) {
                sf::RectangleShape block({block_size,block_size});
                block.setFillColor(mono_grey_medium);
                block.setOutlineThickness(1.f);
                block.setOutlineColor(sf::Color(0,0,0,255));

                char val;
                if (board_val[i] == -1) { val ='M'; }
                else {val = board_val[i] + '0'; }
                switch (val) {
                    case '0':
                        text.setFillColor(sf::Color(0,0,0,0)); break;
                    case 'M':
                        text.setFillColor(sf::Color::Black); break;
                    case  '1':
                        text.setFillColor(mono_blue); break;
                    case '2':
                        text.setFillColor(mono_green); break;
                    case '3':
                        text.setFillColor(mono_yellow); break;
                    case '4':
                        text.setFillColor(mono_orange); break;
                    default:
                        text.setFillColor(mono_red); break;
                }

                block.setPosition({static_cast<float>(i%row)*block_size+offset,static_cast<float>(i/row)*block_size+offset});
                window->draw(block);

                text.setString(val);
                text.setPosition({static_cast<float>(i%row)*block_size+offset+15,static_cast<float>(i/row)*block_size+offset+5});
                window->draw(text);
            }

            else {
                sf::RectangleShape block2({block_size,block_size});
                block2.setPosition({static_cast<float>(i%row)*block_size+offset,static_cast<float>(i/row)*block_size+offset});
                sf::Rect bounding_box = block2.getGlobalBounds();
                sf::Vector2 mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window));

                if (bounding_box.contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left())) {
                    if (board_val[i] == 0) {
                        std::vector<int> visited = {-1};
                        RevealBlankSquares(i, visited);
                        visited.clear();
                    }
                    else if (board_val[i] == -1) {
                        std::cout << "Game Over" << std::endl;
                        board_visible[i] = 1;
                    }
                    else {
                        board_visible[i] = 1;
                    }
                }
                else if (bounding_box.contains(mouse_pos)) {
                    block2.setFillColor(mono_grey_light);
                }
                else {
                    block2.setFillColor(mono_grey_medium_light);
                }
                block2.setOutlineThickness(1.f);
                block2.setOutlineColor(sf::Color(0,0,0,255));

                window->draw(block2);
            }
        }
    }

    const void DrawScoreBoard() {
        float x_offset = 25;
        float y_offset = 850;
        sf::RectangleShape block2({800,100});
        block2.setPosition({x_offset,y_offset});
        block2.setFillColor(mono_grey_medium);
        block2.setOutlineThickness(1.f);
        block2.setOutlineColor(sf::Color(0,0,0,255));

        window->draw(block2);

        text.setCharacterSize(60);
        text.setFillColor(mono_grey_light);
        text.setString(std::to_string((int)clock.getElapsedTime().asSeconds())+"s");
        text.setPosition({25+x_offset,10+y_offset});

        window->draw(text);

        text.setFillColor(sf::Color::Black);
        text.setString(std::to_string(mine_count)+"M");
        text.setPosition({665+x_offset,10+y_offset});

        window->draw(text);
    }

    void RevealBlankSquares(int i, std::vector<int>& visited) {
        auto it = std::find(visited.begin(), visited.end(), i);

        if (board_val[i] == 0 and it == visited.end()) {
            board_visible[i] = 1;
            visited.push_back(i);

            if (i+1 < b_size and (i+1)%row != 0) { RevealBlankSquares(i+1, visited);}
            if (i-1 >= 0 and (i-1)%row != row-1) { RevealBlankSquares(i-1, visited);}

            if (i+row < b_size) { RevealBlankSquares(i+row, visited);}
            if (i-row >= 0) {  RevealBlankSquares(i-row, visited); }

            if (i+1+row < b_size and (i+1+row)%row != 0) { RevealBlankSquares(i+1+row, visited);}
            if (i-1+row < b_size and (i-1+row)%row != row-1) { RevealBlankSquares(i-1+row, visited);}

            if (i+1-row >= 0 and (i+1+row)%row != 0) { RevealBlankSquares(i+1-row, visited);}
            if (i-1-row >= 0 and (i-1+row)%row != row-1) { RevealBlankSquares(i-1-row, visited);}
        }
        else {
            board_visible[i] = 1;
        }
    }

    void PopulateMines() {
        int max_distrib = 7;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution mine_distrib(0, max_distrib);

        for (int i =0; i < b_size; i++) {
            board_visible.push_back(0); // This should be somewhere else
            int gen_num = mine_distrib(gen);
            if (gen_num == 0) {
                board_val.push_back(-1);
                mine_count++;
            }
            else {
                board_val.push_back(0);
            }
        }

        std::uniform_int_distribution space_distrib(0, b_size-1);

        // Populate the board with groups of mines
        while (mine_count < max_mine_count) {
            int gen_num = space_distrib(gen);
            bool near = false;

            if (gen_num+1 < b_size) { if (board_val[gen_num+1] == -1) { near = true; }}
            if (gen_num-1 >= 0) { if (board_val[gen_num-1] == -1) { near = true; }}

            if (gen_num+row < b_size) { if (board_val[gen_num+row] == -1) { near = true; }}
            if (gen_num-row >= 0) {  if (board_val[gen_num-row] == -1) { near = true; }}

            if (board_val[gen_num] != -1 and near) {
                board_val[gen_num] = -1;
                mine_count++;
            }
        }
    }

    void CalculateValuesOnGrid() {
        for (int i = 0; i < row * col; i++) {
            if (board_val[i] == -1) {
                if (i-row-1 >= 0) { if (board_val[i-row-1] != -1 ) { board_val[i-row-1]++;}}
                if (i-row >= 0) { if (board_val[i-row] != -1) { board_val[i-row]++;}}
                if (i-row+1 >= 0) {if (board_val[i-row+1] != -1) { board_val[i-row+1]++;}}

                if (i-1 >= 0) { if (board_val[i-1] != -1) { board_val[i-1]++;}}
                if (i+1 < b_size) { if (board_val[i+1] != -1) { board_val[i+1]++;}}

                if (i+row-1 < b_size) {if (board_val[i+row-1] != -1) { board_val[i+row-1]++;}}
                if (i+row < b_size) {if (board_val[i+row] != -1) { board_val[i+row]++;}}
                if (i+row+1 < b_size) {if (board_val[i+row+1] != -1) { board_val[i+row+1]++;}}
            }
        }
    }

    void HandleKeyboard() {
        switch (game_state) {
            case 0:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {window->close();}
                break;
            case 1:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {game_state = 0;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {std::cout << "Restart" << std::endl;}
                break;
            case 2:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {window->close();}
                break;
        }
    }
};
#endif //BOARDSTATE_H
