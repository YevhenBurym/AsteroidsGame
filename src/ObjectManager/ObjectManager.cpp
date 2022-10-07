#include "ObjectManager.h"

ObjectManager::ObjectManager(GameWindow *window) {
    srand(time(NULL));
    this->map = new Map(window);
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

void ObjectManager::createPlayer() {
    Vector2D avatarCoord{0, 0};
    avatarCoord.setX(this->map->getWMap() / 2 - this->map->getOffset().getX());
    avatarCoord.setY(this->map->getHMap() / 2 - this->map->getOffset().getY());
    this->gameObjects.push_back(
            new SpaceShip(avatarCoord, 0, 0, "spaceship", this->window->getTextureManager(), this->getAmmoLimit(),
                          this->map, this->window->getInputHadler(), &this->gameObjects));
}

void ObjectManager::createAsteroids() {
    if (this->numAsteroids >= this->asteroidsLimit) return;

    this->numAsteroids += 1;

    Vector2D asteroidCoord = this->randomizeAppearCoord();
    Velocity asteroidVelocity = this->randomizeVelocity();
    uint8_t randomAsteroid = 100 * ((double) rand() / RAND_MAX);

    if (randomAsteroid > 80) {
        auto bigAsteroid = new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                           "big_asteroid", this->window->getTextureManager(), this->map);
        this->getObjects().push_back(bigAsteroid);
    } else {
        auto smallAsteroid = new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                               "small_asteroid", this->window->getTextureManager(), this->map);
        this->getObjects().push_back(smallAsteroid);
    }
}

Vector2D ObjectManager::randomizeAppearCoord() {
    double randomNum_0_1 = (double) rand() / RAND_MAX;
    uint8_t randomSide = 3 * randomNum_0_1;
    Vector2D randomXY = {0, 0};

    switch (randomSide) {
        case 0:
            randomXY.setY(randomNum_0_1 * this->map->getHMap() - this->map->getOffset().getY());
            randomXY.setX(randomNum_0_1 * (this->map->getWMap() - this->window->getSize().width) / 2 -
                          this->map->getOffset().getX());
            break;
        case 1:
            randomXY.setX(randomNum_0_1 * this->map->getWMap() - this->map->getOffset().getX());
            randomXY.setY(randomNum_0_1 * (this->map->getHMap() - this->window->getSize().height) / 2 -
                          this->map->getOffset().getY());
            break;
        case 2:
            randomXY.setY(randomNum_0_1 * this->map->getHMap() - this->map->getOffset().getY());
            randomXY.setX(randomNum_0_1 * (this->map->getWMap() - this->window->getSize().width) +
                          this->window->getSize().width -
                          this->map->getOffset().getX());
            break;
        case 3:
            randomXY.setX(randomNum_0_1 * this->map->getWMap() - this->map->getOffset().getX());
            randomXY.setY(randomNum_0_1 * (this->map->getHMap() - this->window->getSize().height) +
                          this->window->getSize().height -
                          this->map->getOffset().getY());
            break;
        default:
            break;
    }
    return randomXY;
}

Velocity ObjectManager::randomizeVelocity() {
    double randomNum_0_1 = (double) rand() / RAND_MAX;
    int minVLimit = 800;
    int maxVLimit = 1600;
    int angleRange = 180;
    Velocity randomV = {0, 0};

    randomV.v = randomNum_0_1 * (maxVLimit - minVLimit) + minVLimit;
    randomV.theta = 2 * (randomNum_0_1 - 0.5) * angleRange;

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
    dynamic_cast<SpaceShip *>(this->gameObjects.front())->getReticle()->render();
}

void ObjectManager::update() {

    this->createAsteroids();
    for (int i = 0; i < this->gameObjects.size(); ++i) {
        this->gameObjects[i]->update();
    }

    this->map->update();
}