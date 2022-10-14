//
// Created by Евгений on 10.10.2022.
//

#include "AutoShootIcon.h"

AutoShootIcon::AutoShootIcon(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : GameObject(coord, {0, 0}, textureID, textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
}

void AutoShootIcon::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
}