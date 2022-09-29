//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "../Game/Game.h"

#include "SDL.h"

class Game;

class InputComponent {
    Game* game;
public:
    InputComponent(Game* game);
    void update();
    void onMouseMove(int x, int y);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
};

class PlayerInputComponent: public InputComponent {
    Game* game;
public:
    PlayerInputComponent(Game* game);
    void handleInput(SDL_Event& event);
    void onMouseMove(int x, int y);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
    void update();
};


