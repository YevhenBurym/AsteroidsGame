//
// Created by Евгений on 16.07.2022.
//

#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
    this->mass = 1;
}