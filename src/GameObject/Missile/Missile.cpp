//
// Created by Евгений on 17.10.2022.
//

#include "Missile.h"

Missile::Missile(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map *map, Asteroid* target, SpaceShip* player)
        : limitator(map), GameObject(coord, Vxy, textureID, textureManager) {
    this->player = player;
    this->target = target;
    if (dynamic_cast<Asteroid*>(target)) {
        dynamic_cast<Asteroid*>(this->target)->attachObservers(this);
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

void Missile::targetIsDestroyedAlready() {
  this->lostTarget = true;
  this->player->setTarget(nullptr);
}