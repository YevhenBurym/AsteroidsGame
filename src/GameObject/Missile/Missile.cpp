//
// Created by Евгений on 17.10.2022.
//

#include "Missile.h"

Missile::Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, GameObject* target)
        : limitator(map), GameObject(coord, Vxy, textureID, textureManager) {
    this->target = target;
    this->map = map;
    this->xyOffset = map->getXY();
    this->velocity = sqrt (Vxy.getX() * Vxy.getX() + Vxy.getY() * Vxy.getY());
}

void Missile::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
    this->guidance();
}

void Missile::guidance() {
    double toDegrees = 180 / M_PI;
    double toRad = 1 / toDegrees;
    //возможно блок try , если вдруг удалился астероид
    if (this->target == nullptr) {
        return;
    }
    Vector2D dirVector = this->getXYrel() - this->target->getXYrel();
    double angle;
    if ((dirVector.getX() == 0) && (dirVector.getY() < 0)) {
        angle = -M_PI / 2;
    } else if ((dirVector.getX() == 0) && (dirVector.getY() > 0)) {
        angle = M_PI / 2;
    } else {
        angle = M_PI - atan2(dirVector.getY(), dirVector.getX());
    }
    angle *= toDegrees;
    this->Vxy = {this->velocity * cos(angle * toRad), -this->velocity * sin(angle * toRad)};
};