//
// Created by Евгений on 17.10.2022.
//

#pragma once

#include "../GameObject.h"
#include "../SpaceShip/SpaceShip.h"
class SpaceShip;
class Missile: public GameObject {
private:
    SpaceShip* player;
    Map* map;
    LimitatorXY limitator;
    GameObject* target;
    double velocity;
    bool lostTarget;
public:
    Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, GameObject* target, SpaceShip* player);
    void guidance();
    void targetIsDestroyedAlready();
    void update() override;
};

