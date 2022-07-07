//
// Created by Евгений on 07.07.2022.
//

#pragma once


#include "GameManager.h"
#include "AsteroidsGame.h"

class AsteroidsGame;

class InputHandler {
    AsteroidsGame* game;
public:
    InputHandler(AsteroidsGame* game);
    void handleInput(SDL_Event& event);
    void onMouseMove(int x, int y, int xrelative, int yrelative);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
};

