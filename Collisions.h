//
// Created by Евгений on 12.07.2022.
//

#pragma once
#include <cmath>
#include <vector>
#include "GameObject.h"
#include "Game.h"


class Collisions {
private:
    Game* game;
    void fixCoord(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween);
    void calcVelocity(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween);
public:
    Collisions(Game* game);
    void check();
};
