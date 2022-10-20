//
// Created by Евгений on 17.10.2022.
//

#pragma once

#include "../SpaceShip/SpaceShip.h"
#include "../Asteroid/Asteroid.h"

class SpaceShip;
class Missile: public GameObject {
private:
    SpaceShip* player;
    Map* map;
    LimitatorXY limitator;
    Asteroid* target;
    double velocity;
    bool lostTarget;
public:
    Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, Asteroid* target, SpaceShip* player);
    void guidance();
    void targetIsDestroyedAlready();
    void update() override;
};

