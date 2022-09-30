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
    void fixCoord(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
    void calcVelocity(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
public:
    Collisions(ObjectManager* objectManager);
    void update();
};
