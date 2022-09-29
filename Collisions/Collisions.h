//
// Created by Евгений on 12.07.2022.
//

#pragma once
#include <cmath>
#include <vector>

#include "../GameObject/SpaceShip.h"
#include "../GameObject/Asteroid.h"
#include "../Game/Game.h"


class Collisions {
private:
    Game* game;
    void fixCoord(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
    void calcVelocity(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
public:
    Collisions(Game* game);
    void check();
};
