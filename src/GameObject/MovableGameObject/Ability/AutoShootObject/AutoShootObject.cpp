//
// Created by Евгений on 10.10.2022.
//

#include "AutoShootObject.h"

AutoShootObject::AutoShootObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : MovableGameObject(coord, 0, 0, textureID, textureManager, map) {
}