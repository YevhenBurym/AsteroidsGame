//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../../GameObject.h"

class AutoShootObject: public GameObject {
private:
    Map* map;
public:
    AutoShootObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
    void update() override;
};

