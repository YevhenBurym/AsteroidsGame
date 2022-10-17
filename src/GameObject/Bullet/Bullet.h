//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../GameObject.h"

class Bullet : public GameObject {
private:
    Map* map;
    LimitatorXY limitator;
public:
    Bullet(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map);
    void update() override;
};