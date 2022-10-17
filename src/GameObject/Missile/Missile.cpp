//
// Created by Евгений on 17.10.2022.
//

#include "Missile.h"
#include "../SmallAsteroid/SmallAsteroid.h"
#include "../BigAsteroid/BigAsteroid.h"

Missile::Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, GameObject* target)
        : limitator(map), GameObject(coord, Vxy, textureID, textureManager) {
    this->target = target;
    if (dynamic_cast<SmallAsteroid*>(target)) {
        dynamic_cast<SmallAsteroid*>(this->target)->attachObservers(this);
    }
    if (dynamic_cast<BigAsteroid*>(target)) {
        dynamic_cast<BigAsteroid*>(this->target)->attachObservers(this);
    }
    this->map = map;
    this->xyOffset = map->getXY();
    this->velocity = sqrt (Vxy.getX() * Vxy.getX() + Vxy.getY() * Vxy.getY());
    this->lostTarget = false;
}

void Missile::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
    if (!this->lostTarget) {
        this->guidance();
    }
}

void Missile::guidance() {
    double toDegrees = 180 / M_PI;
    double toRad = 1 / toDegrees;
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
}

void Missile::targetIsDestroyedAlready(GameObject *item) {
  this->lostTarget = true;
};