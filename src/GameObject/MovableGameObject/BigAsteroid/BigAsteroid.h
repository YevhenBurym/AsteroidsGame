//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../MovableGameObject.h"
#include "../SmallAsteroid/SmallAsteroid.h"

class BigAsteroid : public MovableGameObject {
public:
    BigAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
    void divide(std::vector<MovableGameObject*>& objects);
    void createAbility(std::vector<MovableGameObject*>& buffs);
};
