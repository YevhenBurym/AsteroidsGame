//
// Created by Евгений on 03.10.2022.
//

#pragma once

#include <functional>
#include "../GameObject.h"
#include "../../InputComponent/InputComponent.h"

class Button: public GameObject {
private:
    InputComponent* inputComponent;
    enum ButtonState {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1
    };
    std::function<void()> m_callback;
    bool m_bReleased;
    int currentFrame;
public:
    Button(Vector2D coord, std::string textureID, TextureManager* textureManager, InputComponent *inputComponent, std::function<void()>& callback);
    void render() override;
    void update() override;
};