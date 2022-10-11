//
// Created by Евгений on 06.10.2022.
//

#include "BigAsteroid.h"

BigAsteroid::BigAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager *textureManager,
                         Map *map) : limitator(map), GameObject(coord, velocity, theta, textureID, textureManager) {
    this->map = map;
    this->mass = 2;
}

void BigAsteroid::divide(std::vector<GameObject *> &objects) {
    Vector2D xy1;
    Vector2D xy2;
    xy1.setX(this->coord.getX() /*+ this->xOf*/ + this->radius);
    xy1.setY(this->coord.getY() /*+ this->yOf*/ + this->radius);
    xy2.setX(this->coord.getX() /*+ this->xOf*/ - this->radius);
    xy2.setY(this->coord.getY() /*+ this->yOf*/ - this->radius);


    objects.push_back(
            new SmallAsteroid(xy1, this->V.v, this->V.theta - 45, "small_asteroid", this->textureManager, this->map));
    objects.push_back(
            new SmallAsteroid(xy2, this->V.v, this->V.theta + 45, "small_asteroid", this->textureManager, this->map));
}

void BigAsteroid::createAbility(std::vector<GameObject*>& buffs) {
    buffs.push_back(new ShieldObject(this->coord, "shield_ability", this->textureManager, this->map));
}

void BigAsteroid::update() {
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    GameObject::update();
    this->limitator.limitateXY(this->coord);
}