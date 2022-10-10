//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../../MovableGameObject.h"

class AutoShootObject: public MovableGameObject {
public:
    AutoShootObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
};

