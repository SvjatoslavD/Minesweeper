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
        int max_distrib = 6;
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
        for (int i = b_size/4; i < b_size*3/4; i++) {
            board_visible[i] = 1;
        }
    }

    const sf::Texture CreateGridTextureValues(float block_size) {
        sf::RenderTexture grid({800,800});
        grid.clear(sf::Color(0,0,0,0));
        grid.setRepeated(false);

        sf::Font font = sf::Font("../assets/FiraCode-SemiBold.ttf");
        sf::Text text = sf::Text(font);
        text.setCharacterSize(30);
        text.setScale({1,-1});

        for (int i = 0; i < b_size; i++) {
            if (board_visible[i] == 1) {
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
                text.setString(val);
                text.setPosition({static_cast<float>(i/row)*block_size+15,static_cast<float>(i%row)*block_size+block_size-5});
                grid.draw(text);
            }
            else {
                sf::RectangleShape block2({block_size,block_size});
                block2.setPosition({static_cast<float>(i/row)*block_size,static_cast<float>(i%row)*block_size+block_size-50});
                block2.setFillColor(mono_grey_medium_light);
                block2.setOutlineThickness(1.f);
                block2.setOutlineColor(sf::Color(0,0,0,255));

                grid.draw(block2);
            }
        }

        return grid.getTexture();
    }

    int GetMineCount() { return mine_count; }

private:
    std::array<int,b_size> board_val{0};
    std::array<int,b_size> board_visible{0};
    int mine_count = 0;
    int max_mine_count = 48;
};



#endif //BOARDSTATE_H
