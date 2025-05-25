//
// Created by svjat on 5/17/2025.
//

#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "GameState.h"
#include "GridCell.h"

class PlayingState: public GameState {
public:
    PlayingState(std::string diff, GameManager* game);
    ~PlayingState() override;

    void HandleInput(GameManager* game, sf::Event& event) override;
    void Update(GameManager* game) override;
    void Draw(GameManager* game) override;
    int GetMineCount() const {return player_mine_count;}
    void DecMineCount() {player_mine_count--;}
    void IncMineCount() {player_mine_count++;}

private:
    //Game state variables
    std::string diff;
    sf::Clock clock;
    sf::Texture score_board_tex;
    //Game play variables
    int player_mine_count;
    int true_mine_count = 0;
    int row;
    int col;
    int board_size;
    float block_size;
    bool first_click = true;

    std::vector<GridCell*> grid_cells;

    void CreateGridCells(GameManager* game);
    void UpdateScoreBoard(GameManager* game);
};



#endif //PLAYINGSTATE_H
