//
// Created by Евгений on 16.07.2022.
//

#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, int velocity, int theta, std::string textureID,
                             TextureManager *textureManager, Map *map) : limitator(map),
                                                                         abilityAppearance(textureManager, map),
                                                                         GameObject(coord, velocity, theta, textureID,
                                                                                    textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
    this->mass = 1;
}

void SmallAsteroid::createAbility(std::vector<GameObject *> &buffs) {
    this->abilityAppearance.createAbility(this->xy, buffs);
}

void SmallAsteroid::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
}