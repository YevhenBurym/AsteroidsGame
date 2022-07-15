#include "AsteroidsManager.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX

AsteroidsManager::AsteroidsManager(Game* game) {
    srand(time(NULL));
    this->game = game;
    this->numAsteroids = 0;
    this->asteroidsLimit = game->getAsteroidslimit();
}

void AsteroidsManager::createAsteroids() {
    Vector2D asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 100;
    int maxVLimit = 300;
    int angleRange = 180;
    if (this->numAsteroids < this->asteroidsLimit) {
        this->numAsteroids += 1;

        int wSreen, hSreen;
        this->game->getWindow()->getSize(wSreen, hSreen);

        asteroidCoord = this->randomizeAppearCoord(wSreen, hSreen, this->game->getMap()->getWMap(), this->game->getMap()->getHMap());
        asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

        uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

        if (randomAsteroid > 80) {
            this->game->getObjects().push_back(new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().bigAsteroidSprite, this->game->getMap()));
        } else {
            this->game->getObjects().push_back(new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta, this->game->getMap()->getUnitSprites().smallAsteroidSprite, this->game->getMap()));
        }
    }
}

Vector2D AsteroidsManager::randomizeAppearCoord(int wWindow, int hWindow, int wMap, int hMap) {
    Vector2D randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;

    if (randomSide == 0) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wWindow) / 2 - 0 + 0;
    }
    else if (randomSide == 1) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hWindow) / 2 - 0 + 0;
    }
    else if (randomSide == 2) {
        randomXY.y = RANDRANGE_0_1 * hMap;
        randomXY.x = RANDRANGE_0_1 * (wMap - wWindow) + wWindow;
    }
    else if (randomSide == 3) {
        randomXY.x = RANDRANGE_0_1 * wMap;
        randomXY.y = RANDRANGE_0_1 * (hMap - hWindow) + hWindow;
    }
    return randomXY;
}

Velocity AsteroidsManager::randomizeVelocity(int minVelocity, int maxVelocity, int angleRange) {

    Velocity randomV = {0, 0};

    randomV.v = RANDRANGE_0_1 * (maxVelocity - minVelocity) + minVelocity;
    randomV.theta = 2 * (RANDRANGE_0_1 - 0.5) * angleRange;

    return randomV;
}

int AsteroidsManager::getAsteroidslimit() const {
    return this->asteroidsLimit;
}

int AsteroidsManager::getNumAsteroids() const {
    return this->numAsteroids;
}

void AsteroidsManager::setNumAsteroids(int amount) {
    this->numAsteroids = amount;
}