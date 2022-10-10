//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../../MovableGameObject.h"

class MissileObject: public MovableGameObject {
public:
    MissileObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
};
