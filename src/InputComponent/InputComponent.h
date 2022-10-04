//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "SDL.h"
#include "../Vector2D/Vector2D.h"
#include <vector>
//#include "../ObjectManager/ObjectManager.h"

enum MouseButtons {
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputComponent {
    //SpaceShip* player;
    //ObjectManager* objectManager;
    bool quitGame;
    Vector2D mousePosition;
    std::vector<bool> mouseButtonStates;
    const Uint8* keyStates;
public:
    InputComponent(/*ObjectManager* objectManager*/);
    void update();
    void onMouseMove(int x, int y);
    void onKeyPressed();
    void onKeyReleased();
    void onMouseButtonPressed(int MouseButton);
    void onMouseButtonReleased(int MouseButton);
    Vector2D getMousePosition();
    bool getMouseButtonState(int button);
    void initMouseButtons();
    bool isKeyDown(SDL_Scancode key);
    bool getFlagQuitGame() const;
};

