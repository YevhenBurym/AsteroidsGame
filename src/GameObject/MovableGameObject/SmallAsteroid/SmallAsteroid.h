//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../MovableGameObject.h"

class SmallAsteroid : public MovableGameObject {
public:
    SmallAsteroid (Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
};