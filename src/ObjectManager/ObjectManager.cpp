#include "ObjectManager.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX

void ObjectManager::createPlayer() {
    Vector2D avatarCoord{0, 0};
    avatarCoord.setX(this->map->getWMap() / 2 - this->map->getMapOffsetCoord().getX());
    avatarCoord.setY(this->map->getHMap() / 2 - this->map->getMapOffsetCoord().getY());
    this->gameObjects.push_back(
            new SpaceShip(avatarCoord, 0, 0, "spaceship", this->window->getTextureManager(), this->getAmmoLimit(),
                          this->map, this->window->getInputHadler(), &this->gameObjects));
}

ObjectManager::ObjectManager(GameWindow *window/*, Map *map*/) {
    srand(time(NULL));
    this->map = new Map(window);
    //this->map = map;
    this->window = window;
    this->numAsteroids = 0;
    this->ammoLimit = window->getParameters()->getAmmoLimit();
    this->asteroidsLimit = window->getParameters()->getAsteroidsLimit();
    this->createPlayer();
}

ObjectManager::~ObjectManager() {
    delete this->map;

    for (auto it = this->gameObjects.begin(); it != this->gameObjects.end();) {
        delete (*it++);
    }
    this->gameObjects.clear();
    this->gameObjects.shrink_to_fit();
}

void ObjectManager::createAsteroids() {
    if (this->numAsteroids >= this->asteroidsLimit) return;
    Vector2D asteroidCoord = {0, 0};
    Velocity asteroidVelocity = {0, 0};
    int minVLimit = 800;
    int maxVLimit = 1600;
    int angleRange = 180;
    this->numAsteroids += 1;

    asteroidCoord = this->randomizeAppearCoord();
    asteroidVelocity = this->randomizeVelocity(minVLimit, maxVLimit, angleRange);

    uint8_t randomAsteroid = RANDRANGE_0_1 * 100;

    if (randomAsteroid > 80) {
        auto bigAsteroid = new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                           "big_asteroid", this->window->getTextureManager(), this->map);
        bigAsteroid->setXof(this->map->getXY().getX());
        bigAsteroid->setYof(this->map->getXY().getY());
        this->getObjects().push_back(bigAsteroid);
    } else {
        auto smallAsteroid = new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                               "small_asteroid", this->window->getTextureManager() , this->map);
        smallAsteroid->setXof(this->map->getXY().getX());
        smallAsteroid->setYof(this->map->getXY().getY());
        this->getObjects().push_back(smallAsteroid);
    }
}

Vector2D ObjectManager::randomizeAppearCoord() {
    Vector2D randomXY = {0, 0};
    uint8_t randomSide = RANDRANGE_0_1 * 3;

    if (randomSide == 0) {
        randomXY.setY(RANDRANGE_0_1 * this->map->getHMap() - this->map->getMapOffsetCoord().getY());
        randomXY.setX(RANDRANGE_0_1 * (this->map->getWMap() - this->window->getSize().width) / 2 - this->map->getMapOffsetCoord().getX());
    } else if (randomSide == 1) {
        randomXY.setX(RANDRANGE_0_1 * this->map->getWMap() - this->map->getMapOffsetCoord().getX());
        randomXY.setY(RANDRANGE_0_1 * (this->map->getHMap() - this->window->getSize().height) / 2 - this->map->getMapOffsetCoord().getY());
    } else if (randomSide == 2) {
        randomXY.setY(RANDRANGE_0_1 * this->map->getHMap() - this->map->getMapOffsetCoord().getY());
        randomXY.setX(RANDRANGE_0_1 * (this->map->getWMap() - this->window->getSize().width) + this->window->getSize().width - this->map->getMapOffsetCoord().getX());
    } else if (randomSide == 3) {
        randomXY.setX(RANDRANGE_0_1 * this->map->getWMap() - this->map->getMapOffsetCoord().getX());
        randomXY.setY(RANDRANGE_0_1 * (this->map->getHMap() - this->window->getSize().height) + this->window->getSize().height - this->map->getMapOffsetCoord().getY());
    }
    return randomXY;
}

Velocity ObjectManager::randomizeVelocity(int minVelocity, int maxVelocity, int angleRange) {

    Velocity randomV = {0, 0};

    randomV.v = RANDRANGE_0_1 * (maxVelocity - minVelocity) + minVelocity;
    randomV.theta = 2 * (RANDRANGE_0_1 - 0.5) * angleRange;

    return randomV;
}

std::vector<MovableGameObject *> &ObjectManager::getObjects() {
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

void ObjectManager::render() {
    this->map->render();

    for (auto &object : this->gameObjects) {
        object->render();
    }
    dynamic_cast<SpaceShip*>(this->gameObjects.front())->getReticle()->render();
}

void ObjectManager::update() {

    this->createAsteroids();
    for (int i = 0; i < this->gameObjects.size(); ++i) {
        this->gameObjects[i]->update();
    }
    this->map->update();

    if (this->map->getVxy().getX() != 0 || this->map->getVxy().getY() != 0) {
        for (auto &gameObject : this->gameObjects) {
            gameObject->setXof(this->map->getXY().getX());
            gameObject->setYof(this->map->getXY().getY());
        }
    }
    dynamic_cast<SpaceShip*>(gameObjects.front())->shipHeadAngle();
}