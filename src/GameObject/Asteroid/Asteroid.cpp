//
// Created by Евгений on 20.10.2022.
//

#include "Asteroid.h"

Asteroid::Asteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager,
                         Map *map) : limitator(map), abilityAppearance(textureManager, map),
                                     GameObject(coord, Vxy, textureID, textureManager) {
    this->map = map;
    this->xyOffset = map->getXY();
    this->mass = 1;
    this->observers = new std::set<Missile*>();
}

Asteroid::~Asteroid() {
    Asteroid::notExistNotify();
    delete this->observers;
}

void Asteroid::createAbility(std::vector<AbilityIcon *> &buffs) {
    this->abilityAppearance.createAbility(this->xy, buffs);
}

void Asteroid::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->limitator.limitateXY(this->xy);
}

void Asteroid::attachObservers(Missile* obs) {
    this->observers->insert(obs);
}

void Asteroid::notExistNotify() {
    for (auto observer : *this->observers) {
        observer->targetIsDestroyedAlready();
    }
}
