//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../../MovableGameObject.h"

class ShieldObject: public MovableGameObject {
public:
    ShieldObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
};
