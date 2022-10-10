//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../MovableGameObject.h"
#include "../Ability/ShieldObject/ShieldObject.h"
#include "../Ability/MissileObject/MissileObject.h"
#include "../Ability/AutoShootObject/AutoShootObject.h"
#include "../../../RandomGenerator/RandomGenerator.h"

class SmallAsteroid : public MovableGameObject {
private:
    RandGenerator randGenerator;
public:
    SmallAsteroid (Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
    void createAbility(std::vector<MovableGameObject*>& buffs);
};