//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../MovableGameObject.h"

class Bullet : public MovableGameObject {
public:
    Bullet(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager *textureManager, Map *map);
};