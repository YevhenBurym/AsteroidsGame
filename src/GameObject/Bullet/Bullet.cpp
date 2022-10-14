//
// Created by Евгений on 06.10.2022.
//

#include "Bullet.h"

Bullet::Bullet(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map)
        : limitator(map), GameObject(coord, Vxy, textureID, textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
}


void Bullet::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
}