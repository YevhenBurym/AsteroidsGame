//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "../GameStates/MenuState.h"

class Game {
private:
    GameWindow* gameWindow;
    bool init();
    void update();
    void render();
public:
    Game(GameParameters* parameters);
    ~Game();
    void run();
};