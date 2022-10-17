//
// Created by Евгений on 17.10.2022.
//

#pragma once

#include "../GameObject.h"

class Missile: public GameObject {
private:
    Map* map;
    LimitatorXY limitator;
    GameObject* target;
    double velocity;
    bool lostTarget;
public:
    Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, GameObject* target);
    void guidance();
    void targetIsDestroyedAlready(GameObject* item);
    void update() override;
};

