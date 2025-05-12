//
// Created by svjat on 5/8/2025.
//

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#define row 16
#define col 16
#define b_size 256

#include <array>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "ColorScheme.h"

class BoardState {
public:
    BoardState() {
        int max_distrib = 7;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution mine_distrib(0, max_distrib);

        for (int i =0; i < row * col; i++) {
            int gen_num = mine_distrib(gen);
            if (gen_num == 0) {
                board_val[i] = -1;
                mine_count++;
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
    };

    ~BoardState() {};

    void PrintBoardValues() {
        for (int i = 0; i < b_size; i++) {
            std::cout << board_val[i] << " ";
            if ((i+1)%row == 0) { std::cout << "\n"; }
        }
    };

    void PrintBoardVisible() {
        for (int i = 0; i < b_size; i++) {
            if (board_visible[i] == 0) { std::cout << "x" << " "; }
            else { std::cout << board_val[i] << " "; }

            if ((i+1)%row == 0) { std::cout << "\n"; }
        }
    }

    void TestViewBoard() {
        for (int i = 0; i < b_size; i++) {
            if (i >= b_size*3/4 and board_val[i] != -1) {
                board_visible[i] = 1;
            }
        }
    }

    void DrawGridTextureValues(sf::RenderWindow* window, float block_size, sf::Vector2f mouse_pos) {
        // sf::RenderTexture grid({800,800});
        // grid.clear(sf::Color(0,0,0,0));

        sf::Font font = sf::Font("../assets/FiraCode-SemiBold.ttf");
        sf::Text text = sf::Text(font);
        text.setCharacterSize(30);

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

        // sf::Sprite sprite(grid.getTexture());
        // sprite.setPosition({25,25});
        // window->draw(sprite);
    }

    int GetMineCount() { return mine_count; }

    void RevealBlankSquares(int i, std::vector<int>& visited) {
        auto it = std::find(visited.begin(), visited.end(), i);
        if (board_val[i] == 0 and it == visited.end()) {
            board_visible[i] = 1;
            visited.push_back(i);

            if (i+1 < b_size and (i+1)%row != 0) { RevealBlankSquares(i+1, visited);}
            if (i-1 >= 0 and (i-1)%row != row-1) { RevealBlankSquares(i-1, visited);}

            if (i+row < b_size) { RevealBlankSquares(i+row, visited);}
            if (i-row >= 0) {  RevealBlankSquares(i-row, visited); }

            if (i+1+row < b_size and (i+1)%row != 0) { RevealBlankSquares(i+1+row, visited);}
            if (i-1+row < b_size and( i-1)%row != row) { RevealBlankSquares(i-1+row, visited);}

            if (i+1-row >= 0 and (i+1)%row != 0) { RevealBlankSquares(i+1-row, visited);}
            if (i-1-row >= 0 and (i-1)%row != row) { RevealBlankSquares(i-1-row, visited);}
        }
        else {
            board_visible[i] = 1;
        }
    }

private:
    std::array<int,b_size> board_val{0};
    std::array<int,b_size> board_visible{0};
    int mine_count = 0;
    int max_mine_count = 40;
};



#endif //BOARDSTATE_H
