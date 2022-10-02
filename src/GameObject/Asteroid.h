//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "GameObject.h"

class SmallAsteroid : public GameObject {
public:
    SmallAsteroid (Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
};

class BigAsteroid : public GameObject {
public:
    BigAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
    void divide(std::vector<GameObject*>& objects);
};
