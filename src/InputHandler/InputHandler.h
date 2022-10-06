//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "SDL.h"
#include "../Vector2D/Vector2D.h"
#include <vector>

enum MouseButtons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler {
    bool quitGame;
    Vector2D mousePosition;
    std::vector<bool> mouseButtonStates;
    const Uint8* keyStates;

    void onMouseMove(SDL_Event& event);
    void onMouseButtonPressed(SDL_Event& event);
    void onMouseButtonReleased(SDL_Event& event);
    void onKeyPressed();
    void onKeyReleased();
public:
    InputHandler();
    void update();
    Vector2D getMousePosition();
    bool getMouseButtonState(int button);
    void initMouseButtons();
    bool isKeyDown(SDL_Scancode key);
    bool getFlagQuitGame() const;
};

