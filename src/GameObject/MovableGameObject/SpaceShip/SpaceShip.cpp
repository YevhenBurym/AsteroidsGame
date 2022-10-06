//
// Created by Евгений on 16.07.2022.
//

#include "SpaceShip.h"

void SpaceShip::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().getX();
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().getX();
    double minYCoord = 0 - this->map->getMapOffsetCoord().getY();
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().getY();
    double x = this->coord.getX() + this->xOf;
    double y = this->coord.getY() + this->yOf;
    if (x >= maxXCoord) {
        this->map->setX(minXCoord - this->map->getXY().getX());
    }
    else if (x < minXCoord) {
        this->map->setX(maxXCoord + this->map->getXY().getX());
    }

    if (y >= maxYCoord) {
        this->map->setY(minYCoord - this->map->getXY().getY());
    }
    else if (y < minYCoord) {
        this->map->setY(maxYCoord + this->map->getXY().getY());
    }
}

SpaceShip::SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, int ammoLimit, Map* map, InputHandler* inputHandler, std::vector<MovableGameObject*>* objects) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
    this->reticle = new Reticle("reticle", this->textureManager, map );
    this->angleShip = 0;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
    this->inputHandler = inputHandler;
    this->gameObjects = objects;
    this->buttonLeftPress = false;
}

SpaceShip::~SpaceShip() {
    delete this->reticle;
}

double SpaceShip::getXrel() const {
    return this->coord.getX();
}

double SpaceShip::getYrel() const {
    return this->coord.getY();
}

void SpaceShip::shipHeadAngle() {
    Vector2D avatarCoord{this->coord.getX(), this->coord.getY()};
    Vector2D reticleCoord{this->reticle->getX(), this->reticle->getY()};
    avatarCoord.setX(avatarCoord.getX() - this->map->getXY().getX());
    avatarCoord.setY(avatarCoord.getY() - this->map->getXY().getY());
    reticleCoord.setX(reticleCoord.getX() - this->map->getXY().getX());
    reticleCoord.setY(reticleCoord.getY() - this->map->getXY().getY());

    double alpha = 0;
    Vector2D xyDirVector = {avatarCoord.getX() - reticleCoord.getX(), avatarCoord.getY() - reticleCoord.getY()};

    if ((xyDirVector.getX() == 0) && (xyDirVector.getY() < 0)) {
        alpha = -M_PI / 2;
    } else if ((xyDirVector.getX() == 0) && (xyDirVector.getY() > 0)) {
        alpha = M_PI / 2;
    } else {
        alpha = M_PI - atan2(xyDirVector.getY(), xyDirVector.getX());
    }
    alpha = alpha * 180 / M_PI;
    this->angleShip = alpha; // для розрахунку направлення корабля
}

void SpaceShip::makeShoot(std::vector<MovableGameObject*>& objects) {
    Vector2D avatarCoord{this->coord.getX(), this->coord.getY()};
    avatarCoord.setX(avatarCoord.getX() - this->map->getXY().getX());
    avatarCoord.setY(avatarCoord.getY() - this->map->getXY().getY());
    this->shipHeadAngle();
    if (this->numBullets < this->ammoLimit) {
        this->numBullets += 1;
        auto bullet = new Bullet(avatarCoord, 3500, this->angleShip, "bullet", this->textureManager, this->map);
        bullet->setXof(this->map->getXY().getX());
        bullet->setYof(this->map->getXY().getY());
        objects.push_back(bullet);
    } else {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (dynamic_cast<Bullet*>(*it)) {
                delete (*it);
                objects.erase(it);
                auto bullet = new Bullet(avatarCoord, 3500, this->angleShip, "bullet", this->textureManager, this->map);
                bullet->setXof(this->map->getXY().getX());
                bullet->setYof(this->map->getXY().getY());
                objects.push_back(bullet);
                return;
            }
        }
    }
}

Reticle* SpaceShip::getReticle() const {
    return this->reticle;
}

void SpaceShip::render() const {
    int x = this->coord.getX() - this->radius;
    int y = this->coord.getY() - this->radius;

    this->textureManager->draw(this->textureID,x,y,this->wSprite,this->hSprite,90 - this->angleShip);
}

int SpaceShip::getNumBullets() const {
    return this->numBullets;
}

void SpaceShip::setNumBullets(int amount) {
    this->numBullets = amount;
}

void SpaceShip::update() {
    this->calcCoord();
    Vector2D mousePos = this->inputHandler->getMousePosition();
    this->reticle->setX(mousePos.getX());
    this->reticle->setY(mousePos.getY());

    if (this->inputHandler->getMouseButtonState(LEFT) && !this->buttonLeftPress) {
        this->buttonLeftPress = true;
        this->makeShoot(*this->gameObjects);
    } else if (!this->inputHandler->getMouseButtonState(LEFT)) {
        this->buttonLeftPress = false;
    }
}