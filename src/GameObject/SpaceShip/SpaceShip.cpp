//
// Created by Евгений on 16.07.2022.
//

#include "SpaceShip.h"

void SpaceShip::limitateXY() {

    double x = this->xy.getX() + this->map->getXY().getX();
    double y = this->xy.getY() + this->map->getXY().getY();
    if (x >= this->map->getMaxCoord().getX()) {
        this->map->setX(this->map->getMinCoord().getX() - this->map->getXY().getX());
    } else if (x < this->map->getMinCoord().getX()) {
        this->map->setX(this->map->getMaxCoord().getX() + this->map->getXY().getX());
    }

    if (y >= this->map->getMaxCoord().getY()) {
        this->map->setY(this->map->getMinCoord().getY() - this->map->getXY().getY());
    } else if (y < this->map->getMinCoord().getY()) {
        this->map->setY(this->map->getMaxCoord().getY() + this->map->getXY().getY());
    }
}

SpaceShip::SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager *textureManager,
                     int ammoLimit, Map *map, InputHandler *inputHandler, std::vector<GameObject *> *bullets)
        : GameObject(coord, velocity, theta, textureID, textureManager) {
    this->map = map;
    this->reticle = new Reticle("reticle", this->textureManager);
    this->angleShip = 0;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
    this->inputHandler = inputHandler;
    this->bullets = bullets;
    this->buttonLeftPress = false;
}

SpaceShip::~SpaceShip() {
    delete this->reticle;
}

Vector2D SpaceShip::getXYrel() const {
    return this->xy;
}

void SpaceShip::shipHeadAngle() {
    double toDegrees = 180 / M_PI;
    Vector2D avatarXY = this->xy - this->map->getXY();
    Vector2D reticleXY = this->reticle->getXY() - this->map->getXY();
    Vector2D dirVector = avatarXY - reticleXY;

    if ((dirVector.getX() == 0) && (dirVector.getY() < 0)) {
        this->angleShip = -M_PI / 2;
    } else if ((dirVector.getX() == 0) && (dirVector.getY() > 0)) {
        this->angleShip = M_PI / 2;
    } else {
        this->angleShip = M_PI - atan2(dirVector.getY(), dirVector.getX());
    }
    this->angleShip *= toDegrees;
}

void SpaceShip::makeShoot(std::vector<GameObject *> &bulletsVec) {
    Vector2D avatarCoord{this->xy.getX(), this->xy.getY()};
    avatarCoord.setX(avatarCoord.getX() - this->map->getXY().getX());
    avatarCoord.setY(avatarCoord.getY() - this->map->getXY().getY());
    this->shipHeadAngle();
    if (this->numBullets < this->ammoLimit) {
        this->numBullets += 1;
        bulletsVec.push_back(new Bullet(avatarCoord, 3500, this->angleShip, "bullet", this->textureManager, this->map));
    } else {
        delete *bulletsVec.begin();
        bulletsVec.erase(bulletsVec.begin());
        bulletsVec.push_back(new Bullet(avatarCoord, 3500, this->angleShip, "bullet", this->textureManager, this->map));
    }
}

Reticle *SpaceShip::getReticle() const {
    return this->reticle;
}

int SpaceShip::getNumBullets() const {
    return this->numBullets;
}

void SpaceShip::setNumBullets(int amount) {
    this->numBullets = amount;
}

void SpaceShip::update() {
    GameObject::update();
    limitateXY();

    this->reticle->setXY(this->inputHandler->getMousePosition());
    this->shipHeadAngle();

    if (this->inputHandler->getMouseButtonState(LEFT) && !this->buttonLeftPress) {
        this->buttonLeftPress = true;
        this->makeShoot(*this->bullets);
    } else if (!this->inputHandler->getMouseButtonState(LEFT)) {
        this->buttonLeftPress = false;
    }

}

void SpaceShip::render() {
    int x = this->xy.getX() - this->radius;
    int y = this->xy.getY() - this->radius;

    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite, 90 - this->angleShip);
}