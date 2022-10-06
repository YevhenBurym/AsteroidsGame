//
// Created by Евгений on 06.10.2022.
//

#include "Bullet.h"

Bullet::Bullet(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager *textureManager, Map *map)
        : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {}