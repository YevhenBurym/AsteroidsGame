//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "GameState.h"

class GameStateMachine {
public:
    void pushState(GameState *pState);

    void changeState(GameState *pState);

    void popState();

    void update();

    void render();

private:
    std::vector<GameState *> m_gameStates;
};
