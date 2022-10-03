//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "SDL.h"
#include "../ObjectManager/ObjectManager.h"

enum MouseButtons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputComponent {
    SpaceShip* player;
    ObjectManager* objectManager;
    Map* map;
    bool quitGame;
    Vector2D mousePosition;
    std::vector<bool> mouseButtonStates;
public:
    InputComponent(ObjectManager* objectManager, Map* map);
    void update();
    void onMouseMove(int x, int y);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
    bool getFlagQuitGame() const;
    Vector2D getMousePosition();
    bool getMouseButtonState(int button);
    void initMouseButtons();
};

