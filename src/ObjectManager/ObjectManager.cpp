#include "ObjectManager.h"

ObjectManager::ObjectManager(GameWindow *window) {
    this->map = new Map(window);
    this->window = window;
    this->numAsteroids = 0;
    this->ammoLimit = window->getParameters()->getAmmoLimit();
    this->asteroidsLimit = window->getParameters()->getAsteroidsLimit();
    this->createPlayer();
    this->randGenerator = RandGenerator();
}

ObjectManager::~ObjectManager() {
    delete this->map;
    delete this->player;

    for (auto it = this->asteroids.begin(); it != this->asteroids.end();) {
        delete (*it++);
    }
    this->asteroids.clear();
    this->asteroids.shrink_to_fit();
    for (auto it = this->bullets.begin(); it != this->bullets.end();) {
        delete (*it++);
    }
    this->bullets.clear();
    this->bullets.shrink_to_fit();
}

void ObjectManager::createPlayer() {
    Vector2D avatarCoord{0, 0};
    avatarCoord.setX(this->map->getWMap() / 2 - this->map->getOffset().getX());
    avatarCoord.setY(this->map->getHMap() / 2 - this->map->getOffset().getY());
    this->player = new SpaceShip(avatarCoord, 0, 0, "spaceship", this->window->getTextureManager(), this->getAmmoLimit(),
                                 this->map, this->window->getInputHadler(), &this->bullets);
}

void ObjectManager::createAsteroids() {
    if (this->numAsteroids >= this->asteroidsLimit) return;

    this->numAsteroids += 1;

    Vector2D asteroidCoord = this->randomizeAppearCoord();
    Velocity asteroidVelocity = this->randomizeVelocity();

    if (this->randGenerator.getRandNumber() > 0.8) {
        auto bigAsteroid = new BigAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                           "big_asteroid", this->window->getTextureManager(), this->map);
        this->asteroids.push_back(bigAsteroid);
    } else {
        auto smallAsteroid = new SmallAsteroid(asteroidCoord, asteroidVelocity.v, asteroidVelocity.theta,
                                               "small_asteroid", this->window->getTextureManager(), this->map);
        this->asteroids.push_back(smallAsteroid);
    }
}

Vector2D ObjectManager::randomizeAppearCoord() {
    uint8_t randomSide = 3 * this->randGenerator.getRandNumber();
    Vector2D randomXY = {0, 0};

    switch (randomSide) {
        case 0:
            randomXY.setY(this->randGenerator.getRandNumber() * this->map->getHMap() - this->map->getOffset().getY());
            randomXY.setX(this->randGenerator.getRandNumber() * (this->map->getWMap() - this->window->getSize().width) / 2 -
                          this->map->getOffset().getX());
            break;
        case 1:
            randomXY.setX(this->randGenerator.getRandNumber() * this->map->getWMap() - this->map->getOffset().getX());
            randomXY.setY(this->randGenerator.getRandNumber() * (this->map->getHMap() - this->window->getSize().height) / 2 -
                          this->map->getOffset().getY());
            break;
        case 2:
            randomXY.setY(this->randGenerator.getRandNumber() * this->map->getHMap() - this->map->getOffset().getY());
            randomXY.setX(this->randGenerator.getRandNumber() * (this->map->getWMap() - this->window->getSize().width) +
                          this->window->getSize().width -
                          this->map->getOffset().getX());
            break;
        case 3:
            randomXY.setX(this->randGenerator.getRandNumber() * this->map->getWMap() - this->map->getOffset().getX());
            randomXY.setY(this->randGenerator.getRandNumber() * (this->map->getHMap() - this->window->getSize().height) +
                          this->window->getSize().height -
                          this->map->getOffset().getY());
            break;
        default:
            break;
    }
    return randomXY;
}

Velocity ObjectManager::randomizeVelocity() {
    int minVLimit = 800;
    int maxVLimit = 1600;
    int angleRange = 180;
    Velocity randomV = {0, 0};

    randomV.v = this->randGenerator.getRandNumber() * (maxVLimit - minVLimit) + minVLimit;
    randomV.theta = 2 * (this->randGenerator.getRandNumber() - 0.5) * angleRange;

    return randomV;
}

std::vector<MovableGameObject *> &ObjectManager::getAsteroids() {
    return this->asteroids;
}
std::vector<MovableGameObject *> &ObjectManager::getBullets() {
    return this->bullets;
}

std::vector<MovableGameObject *> &ObjectManager::getBuffs() {
    return this->buffs;
}

SpaceShip* ObjectManager::getPlayer() {
    return this->player;
}

int ObjectManager::getAmmoLimit() const {
    return this->ammoLimit;
}

int ObjectManager::getNumAsteroids() const {
    return this->numAsteroids;
}

double ObjectManager::getAbilityProbability() const {
    return this->window->getParameters()->getAbilityProbability();
}

void ObjectManager::setNumAsteroids(int amount) {
    this->numAsteroids = amount;
}

void ObjectManager::render() {
    this->map->render();
    this->player->render();

    for (auto &bullet : this->bullets) {
        bullet->render();
    }

    for (auto &asteroid : this->asteroids) {
        asteroid->render();
    }

    for (auto & buf : this->buffs) {
        buf->render();
    }

    this->player->getReticle()->render();
}

void ObjectManager::update() {
    this->map->update();
    this->player->update();

    for (auto & bullet : this->bullets) {
        bullet->update();
    }

    this->createAsteroids();
    for (auto & asteroid : this->asteroids) {
        asteroid->update();
    }

    for (auto & buf : this->buffs) {
        buf->update();
    }
}
