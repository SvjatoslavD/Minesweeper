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
        std::uniform_int_distribution distrib(0, max_distrib);

        for (int i =0; i < row * col; i++) {
            int gen_num = distrib(gen);
            if (gen_num == 0) {
                board_val[i] = -1;
                mine_count++;
            }
        }

        while (mine_count < max_mine_count) {
            max_distrib += 2;
            std::vector<int> saved_spaces{};

            for (int i =0; i < row * col; i++) {
                int gen_num = distrib(gen);
                if (i <= row) {
                    if (board_val[i+row] == -1 || board_val[i+1] == -1) {
                        if (gen_num == 0) {
                            saved_spaces.push_back(i);
                        }
                    }
                }

                else if (i >= (b_size-row)) {
                    if (board_val[i-row] == -1 || board_val[i-1] == -1) {
                        if (gen_num == 0) {
                            saved_spaces.push_back(i);
                        }
                    }
                }

                else {
                    if (board_val[i-row] == -1 || board_val[i+row] == -1 || board_val[i-1] == -1 || board_val[i+1] == -1) {
                        if (gen_num == 0) {
                            saved_spaces.push_back(i);
                        }
                    }
                }
            }

            for (int num : saved_spaces) {
                board_val[num] = -1;
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
            board_visible[i] = 1;
        }
    }

    const sf::Texture CreateGridTextureValues(float block_size) {
        sf::RenderTexture grid({800,800});
        grid.clear(sf::Color(0,0,0,0));

        sf::Font font = sf::Font("../assets/FiraCode-SemiBold.ttf");
        sf::Text text = sf::Text(font);
        text.setCharacterSize(30);
        text.setScale({1,-1});

        for (int i = 0; i < b_size; i++) {
            if (board_visible[i] == 1 && board_val[i] != 0) {
                char val;
                if (board_val[i] == -1) { val ='M'; }
                else {val = board_val[i] + '0'; }
                switch (val) {
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
        }

        return grid.getTexture();
    }

    int GetMineCount() { return mine_count; }

private:
    std::array<int,b_size> board_val{0};
    std::array<int,b_size> board_visible{0};
    int mine_count = 0;
    int max_mine_count = 50;
};



#endif //BOARDSTATE_H
