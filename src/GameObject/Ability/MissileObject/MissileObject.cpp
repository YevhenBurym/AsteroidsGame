//
// Created by Евгений on 10.10.2022.
//

#include "MissileObject.h"

MissileObject::MissileObject (Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : GameObject(coord, 0, 0, textureID, textureManager) {
    this->map = map;
}

void MissileObject::update() {
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    GameObject::update();
}