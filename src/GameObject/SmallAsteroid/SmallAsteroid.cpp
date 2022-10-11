//
// Created by Евгений on 16.07.2022.
//

#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map) : limitator(map), GameObject(coord, velocity, theta, textureID, textureManager) {
    this->map = map;
    this->mass = 1;
    this->randGenerator = RandGenerator();
}

void SmallAsteroid::createAbility(std::vector<GameObject*>& buffs) {
    double randomAbility = this->randGenerator.getRandNumber();

    if (this->randGenerator.getRandNumber() <= 0.3) {
        if (randomAbility <= 0.35) {
            buffs.push_back(new ShieldObject(this->coord, "shield_ability", this->textureManager, this->map));
        } else if (randomAbility <= 0.65) {
            buffs.push_back(new MissileObject(this->coord, "missile_ability", this->textureManager, this->map));
        } else {
            buffs.push_back(new AutoShootObject(this->coord, "autoshoot_ability", this->textureManager, this->map));
        }
    }
}

void SmallAsteroid::update() {
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    GameObject::update();
    this->limitator.limitateXY(this->coord);
}
