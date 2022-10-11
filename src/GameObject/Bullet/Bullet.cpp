//
// Created by Евгений on 06.10.2022.
//

#include "Bullet.h"

Bullet::Bullet(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager *textureManager, Map *map)
        : limitator(map), GameObject(coord, velocity, theta, textureID, textureManager) {
    this->map = map;
}


void Bullet::update() {
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    GameObject::update();
    this->limitator.limitateXY(this->coord);
}