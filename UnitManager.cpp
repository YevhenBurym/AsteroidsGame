#include "UnitManager.h"

UnitManager::UnitManager(Game* game) {
    srand(time(NULL));
    this->game = game;
    int wSprite, hSprite;
    this->game->getMap()->getUnitSprites().reticleSprite->getSize(wSprite, hSprite);
    this->isNeedDeAcc = false;
}

void UnitManager::createAsteroids() {
    CoordXY asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 100;
    int maxVLimit = 300;
    int angleRange = 180;
    if (this->game->getNumAsteroids() < this->game->getAsteroidslimit()) {
        int newAmountAsteroids = this->game->getNumAsteroids() + 1;
        this->game->setNumAsteroids(newAmountAsteroids);
        asteroidCoord = this->randomizeAppearCoord(this->game->getMap()->getWMap(), this->game->getMap()->getHMap());
        asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

        uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

        if (randomAsteroid > 80) {
            this->game->getObjects().push_back(new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().bigAsteroidSprite, this->game->getMap()));
        } else {
            this->game->getObjects().push_back(new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
        }
    }
}

CoordXY UnitManager::randomizeAppearCoord(int wMap, int hMap) {
    CoordXY randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;
    int wSreen, hSreen;
    this->game->getWindow()->getSize(wSreen, hSreen);

    if (randomSide == 0) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wSreen) / 2 - 0 + 0;
    }
    else if (randomSide == 1) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hSreen) / 2 - 0 + 0;
    }
    else if (randomSide == 2) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wSreen) + wSreen;
    }
    else if (randomSide == 3) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hSreen) + hSreen;
    }
    return randomXY;
}

Velocity UnitManager::randomizeVelocity(int minVelocity, int maxVelocity, int angleRange) {

    Velocity randomV = {0, 0};

    randomV.v = RANDRANGE_0_1 * (maxVelocity - minVelocity) + minVelocity;
    randomV.theta = 2 * (RANDRANGE_0_1 - 0.5) * angleRange;

    return randomV;
}

void UnitManager::drawAsteroids() {
    for (auto & object : this->game->getObjects()) {
        object->calcCoord(object->getVx(), object->getVy(), 0.001);
        object->draw();
    }
}

void UnitManager::calcObjectOffset() {
    this->game->getMap()->calcCoord(this->game->getMap()->getVx(), this->game->getMap()->getVy(), 0.001);

    if (this->game->getMap()->getV().v) {
        for (auto it = this->game->getObjects().begin(); it != this->game->getObjects().end(); ++it) {
            (*it)->setXof(this->game->getMap()->getX());
            (*it)->setYof(this->game->getMap()->getY());
        }
    }
}


void UnitManager::deAcceleration() {
    double step = 0.001;
    double acc = 500;
    double vMap = this->game->getMap()->getV().v;
    double thetaMap = this->game->getMap()->getV().theta;
    if (isNeedDeAcc) {
        if (vMap > 0) {
            vMap -= acc * step;
        }
        else {
            isNeedDeAcc = false;
        }
        this->game->getMap()->setV(vMap, thetaMap);
    }
}

void UnitManager::setIsNeededDeacc(bool state) {
    this->isNeedDeAcc = true;
}
