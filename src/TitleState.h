//
// Created by svjat on 5/17/2025.
//

#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "GameState.h"

class TitleState: public GameState {
public:
    TitleState();
    ~TitleState() override;

    void Pause() override;
    void Resume() override;

    void HandleInput(GameManager* game) override;
    void Update(GameManager* game) override;
    void Draw(GameManager* game) override;
};



#endif //TITLESTATE_H
