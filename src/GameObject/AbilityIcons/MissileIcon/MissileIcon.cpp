//
// Created by Евгений on 10.10.2022.
//

#include "MissileIcon.h"

MissileIcon::MissileIcon (Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : GameObject(coord, {0, 0}, textureID, textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
}

void MissileIcon::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
}