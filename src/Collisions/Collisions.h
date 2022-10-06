//
// Created by Евгений on 12.07.2022.
//

#pragma once

#include <cmath>
#include "../ObjectManager/ObjectManager.h"

class YouDied {};

class Collisions {
private:
    ObjectManager* objectManager;
    void fixCoord(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween);
    void calcVelocity(MovableGameObject* unit1, MovableGameObject* unit2, Vector2D vectorBetween);
public:
    explicit Collisions(ObjectManager* objectManager);
    void update();
};
