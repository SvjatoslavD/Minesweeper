//
// Created by svjat on 5/17/2025.
//

#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "GameState.h"

class PlayingState: public GameState {
public:
    PlayingState(std::string diff, GameManager* game);
    ~PlayingState() override;

    void HandleInput(GameManager* game) override;
    void Update(GameManager* game) override;
    void Draw(GameManager* game) override;
    void UpdateScoreBoard(GameManager* game);

private:
    std::string diff;
    sf::Clock clock;
    sf::Texture score_board_tex;
    //Game variables
    int player_mine_count;
    int true_mine_count = 0;
    int row;
    int col;
    int board_size;
    bool first_click = true;
};



#endif //PLAYINGSTATE_H
