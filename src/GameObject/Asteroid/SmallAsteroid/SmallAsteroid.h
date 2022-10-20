//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../Asteroid.h"

class SmallAsteroid : public Asteroid {
public:
    SmallAsteroid (Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
};