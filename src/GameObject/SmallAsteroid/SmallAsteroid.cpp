//
// Created by Евгений on 16.07.2022.
//

#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID,
                             TextureManager *textureManager, Map *map) : limitator(map),
                                                                         abilityAppearance(textureManager, map),
                                                                         GameObject(coord, Vxy, textureID,
                                                                                    textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
    this->mass = 1;
    this->observers = new std::set<Missile*>();
}

SmallAsteroid::~SmallAsteroid() {
    this->notExistNotify();
    delete this->observers;
}

void SmallAsteroid::createAbility(std::vector<AbilityIcon *> &buffs) {
    this->abilityAppearance.createAbility(this->xy, buffs);
}

void SmallAsteroid::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
}

void SmallAsteroid::attachObservers(Missile* obs) {
    this->observers->insert(obs);
}

void SmallAsteroid::notExistNotify() {
    for (auto observer : *this->observers) {
        observer->targetIsDestroyedAlready();
    }
}