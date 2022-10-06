//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "../GameStates/MenuState/MenuState.h"

class Game {
private:
    GameWindow* gameWindow;
    void init();
    void update();
    void render();
public:
    explicit Game(GameParameters* parameters);
    ~Game();
    void run();
};