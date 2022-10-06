//
// Created by Евгений on 03.10.2022.
//

#pragma once

#include "../GameObject.h"

class GameOverMessage: public GameObject {
private:
    int animationSpeed;
    int currentFrame;
public:
    GameOverMessage(Vector2D coord, std::string textureID, TextureManager* textureManager, int animationSpeed);
    void render() override;
    void update() override;
};
