//
// Created by svjat on 5/18/2025.
//

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include "Button.h"
class PlayingState;

class GridCell: public Button {
public:
    GridCell(float x, float y, float h, float w, sf::Color standard, sf::Color hover, GameManager* game);
    ~GridCell();

    void MouseClickRight(GameManager* game, PlayingState* playing_state);
    void MouseClickLeft(GameManager* game, PlayingState* playing_state);
    bool LostGame();
    void Draw(GameManager* game);

private:
    // -1 is a mine, 0 is empty, numbers indicate the number of adjacent mines
    int value = 0;
    // 0 is visible, 1 is hidden, 2 is flagged as Mine, 3 is flagged as unknown
    int visible = 1;
};



#endif //GRIDCELL_H
