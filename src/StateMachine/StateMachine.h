//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "../GameStates/GameState.h"

class StateMachine {
private:
    GameState* needToDelete;
    bool isChange;
    std::vector<GameState *> gameStates;
public:
    StateMachine();
    void pushState(GameState *pState);
    void changeState(GameState *pState);
    void popState();
    void update();
    void render();
    bool needToErasePrevState();

};
