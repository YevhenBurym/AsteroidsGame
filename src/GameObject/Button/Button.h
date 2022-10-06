//
// Created by Евгений on 03.10.2022.
//

#pragma once

#include <functional>
#include "../GameObject.h"
#include "../../InputHandler/InputHandler.h"

class Button: public GameObject {
private:
    InputHandler* inputHandler;
    enum ButtonState {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1
    };
    std::function<void()> callbackFunction;
    bool isButtonReleased;
    int currentFrame;
public:
    Button(Vector2D coord, std::string textureID, TextureManager* textureManager,
            InputHandler *inputComponent, std::function<void()>& callbackFunction);
    void render() override;
    void update() override;
};