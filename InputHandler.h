//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "Game.h"

class Game;


class InputHandler {
    Game* game;
public:
    InputHandler(Game* game);
    void handleInput(SDL_Event& event);
    void onMouseMove(int x, int y, int xrelative, int yrelative);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
};

class PlayerInputHandler: public InputHandler {
    Game* game;
public:
    PlayerInputHandler(Game* game);
    void handleInput(SDL_Event& event);
    void onMouseMove(int x, int y, int xrelative, int yrelative);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
};


