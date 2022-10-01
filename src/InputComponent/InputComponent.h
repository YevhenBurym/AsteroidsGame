//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "SDL.h"
#include "../ObjectManager/ObjectManager.h"

class InputComponent {
    SpaceShip* player;
    ObjectManager* objectManager;
    Map* map;
    bool quitGame;
public:
    InputComponent(ObjectManager* objectManager, Map* map);
    void update();
    void onMouseMove(int x, int y);
    void onKeyPressed(SDL_Keycode key);
    void onKeyReleased(SDL_Keycode key);
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
    bool getFlagQuitGame() const;
};

