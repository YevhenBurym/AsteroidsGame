#include "ObjectManager.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX

void ObjectManager::createPlayer() {
    Vector2D avatarCoord{0, 0};
    avatarCoord.setX(this->map->getWMap() / 2 - this->map->getMapOffsetCoord().getX());
    avatarCoord.setY(this->map->getHMap() / 2 - this->map->getMapOffsetCoord().getY());
    this->gameObjects.push_back(
            new SpaceShip(avatarCoord, 0, 0, this->map->getUnitSprites().spaceshipSprite, this->getAmmoLimit(),
                          this->map));
}

ObjectManager::ObjectManager(GameWindow *window, Map *map, int asteroidsLimit, int ammoLimit) {
    srand(time(NULL));
    this->map = map;
    this->window = window;
    this->numAsteroids = 0;
    this->ammoLimit = ammoLimit;
    this->asteroidsLimit = asteroidsLimit;
    this->createPlayer();
}

void ObjectManager::createAsteroids() {
    if (this->numAsteroids >= this->asteroidsLimit) return;
    Vector2D asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 100;
    int maxVLimit = 300;
    int angleRange = 180;
    this->numAsteroids += 1;

    int wScreen = this->window->getSize().width;
    int hScreen = this->window->getSize().height;

    asteroidCoord = this->randomizeAppearCoord(wScreen, hScreen, this->map->getWMap(), this->map->getHMap());
    asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

    uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

    if (randomAsteroid > 80) {
        this->getObjects().push_back(new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                                     this->map->getUnitSprites().bigAsteroidSprite, this->map));
    } else {
        this->getObjects().push_back(new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                                       this->map->getUnitSprites().smallAsteroidSprite, this->map));
    }
}

Vector2D ObjectManager::randomizeAppearCoord(int wWindow, int hWindow, int wMap, int hMap) {
    Vector2D randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;

    if (randomSide == 0) {
        randomXY.setY(RANDRANGE_0_1 * hMap);
        randomXY.setX(RANDRANGE_0_1 * (wMap - wWindow) / 2 - 0 + 0);
    } else if (randomSide == 1) {
        randomXY.setX(RANDRANGE_0_1 * wMap);
        randomXY.setY(RANDRANGE_0_1 * (hMap - hWindow) / 2 - 0 + 0);
    } else if (randomSide == 2) {
        randomXY.setY(RANDRANGE_0_1 * hMap);
        randomXY.setX(RANDRANGE_0_1 * (wMap - wWindow) + wWindow);
    } else if (randomSide == 3) {
        randomXY.setX(RANDRANGE_0_1 * wMap);
        randomXY.setY(RANDRANGE_0_1 * (hMap - hWindow) + hWindow);
    }
    return randomXY;
}

Velocity ObjectManager::randomizeVelocity(int minVelocity, int maxVelocity, int angleRange) {

    Velocity randomV = {0, 0};

    randomV.v = RANDRANGE_0_1 * (maxVelocity - minVelocity) + minVelocity;
    randomV.theta = 2 * (RANDRANGE_0_1 - 0.5) * angleRange;

    return randomV;
}

std::vector<GameObject *> &ObjectManager::getObjects() {
    return this->gameObjects;
}

int ObjectManager::getAmmoLimit() const {
    return this->ammoLimit;
}

int ObjectManager::getNumAsteroids() const {
    return this->numAsteroids;
}

void ObjectManager::setNumAsteroids(int amount) {
    this->numAsteroids = amount;
}

ObjectManager::~ObjectManager() {
    for (auto it = this->gameObjects.begin(); it != this->gameObjects.end();) {
        delete (*it++);
    }
    this->gameObjects.clear();
    this->gameObjects.shrink_to_fit();
}

void ObjectManager::render() {
    for (auto &object : this->gameObjects) {
        object->calcCoord(object->getVxy(), 0.001);
        object->render();
    }
    dynamic_cast<SpaceShip*>(this->gameObjects.front())->getReticle()->render();
}

void ObjectManager::update() {
    this->createAsteroids();

    this->map->calcCoord(this->map->getVx(), this->map->getVy(), 0.5);

    if (this->map->getVx() != 0 || this->map->getVy() != 0) {
        for (auto &gameObject : this->gameObjects) {
            gameObject->setXof(this->map->getX());
            gameObject->setYof(this->map->getY());
        }
    }

    dynamic_cast<SpaceShip*>(gameObjects.front())->shipHeadAngle();
}