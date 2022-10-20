//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../SmallAsteroid/SmallAsteroid.h"
#include "../Asteroid.h"

class BigAsteroid : public Asteroid {
public:
    BigAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    void divide(std::vector<Asteroid*>& objects);
};
