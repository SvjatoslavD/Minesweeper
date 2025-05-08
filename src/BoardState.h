//
// Created by svjat on 5/8/2025.
//

#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#define row 16
#define col 16
#define b_size row*col

#include <array>
#include <iostream>
#include <random>

class BoardState {
public:
    BoardState() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution distrib(0, 5);

        for (int i =0; i < row * col; i++) {
            int gen_num = distrib(gen);
            if (gen_num == 5) {
                board_val[i] = -1;
            }
        }

        std::vector<int> saved_spaces{};

        for (int i =0; i < row * col; i++) {
            int gen_num = distrib(gen);
            if (i <= row) {
                if (board_val[i+row] == -1 || board_val[i+1] == -1) {
                    if (gen_num == 5) {
                        saved_spaces.push_back(i);
                    }
                }
            }

            else if (i >= (b_size-row)) {
                if (board_val[i-row] == -1 || board_val[i-1] == -1) {
                    if (gen_num == 5) {
                        saved_spaces.push_back(i);
                    }
                }
            }

            else {
                if (board_val[i-row] == -1 || board_val[i+row] == -1 || board_val[i-1] == -1 || board_val[i+1] == -1) {
                    if (gen_num == 5) {
                        saved_spaces.push_back(i);
                    }
                }
            }
        }

        for (int num : saved_spaces) {
            board_val[num] = -1;
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

    void TestViewHalfBoard() {
        for (int i = b_size/4; i < b_size*3/4; i++) {
            board_visible[i] = 1;
        }
    }

private:
    std::array<int,b_size> board_val{0};
    std::array<int,b_size> board_visible{0};
};



#endif //BOARDSTATE_H
