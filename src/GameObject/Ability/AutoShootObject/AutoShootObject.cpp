//
// Created by Евгений on 10.10.2022.
//

#include "AutoShootObject.h"

AutoShootObject::AutoShootObject(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : GameObject(coord, 0, 0, textureID, textureManager) {
    this->map = map;
}

void AutoShootObject::update() {
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    GameObject::update();
}