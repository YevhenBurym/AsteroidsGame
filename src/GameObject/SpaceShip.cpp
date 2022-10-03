//
// Created by Евгений on 16.07.2022.
//

#include "SpaceShip.h"

Bullet::Bullet(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
}

void SpaceShip::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().getX();
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().getX();
    double minYCoord = 0 - this->map->getMapOffsetCoord().getY();
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().getY();
    double x = this->coord.getX() + this->xOf;
    double y = this->coord.getY() + this->yOf;
    if (x >= maxXCoord) {
        this->map->setX(minXCoord - this->map->getX());
    }
    else if (x < minXCoord) {
        this->map->setX(maxXCoord + this->map->getX());
    }

    if (y >= maxYCoord) {
        this->map->setY(minYCoord - this->map->getY());
    }
    else if (y < minYCoord) {
        this->map->setY(maxYCoord + this->map->getY());
    }
}

SpaceShip::SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, int ammoLimit, Map* map) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
    this->reticle = new Reticle("reticle", this->textureManager, map );
    this->angleShip = 0;
    this->ammoLimit = ammoLimit;
    this->numBullets = 0;
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
    int xAvatar = this->coord.getX();
    int yAvatar = this->coord.getY();
    double xRet = this->reticle->getX();
    double yRet = this->reticle->getY();
    if ( this->map->getVx() != 0 || this->map->getVy() != 0 ) {
        xAvatar -= this->map->getX();
        yAvatar -= this->map->getY();
        xRet -= this->map->getX();
        yRet -= this->map->getY();
    }
    double alpha = 0;
    Vector2D xyDirVector = {xAvatar - xRet, yAvatar - yRet };

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
    this->shipHeadAngle();
    if ( this->map->getVx() != 0 || this->map->getVy() != 0 ) {
        avatarCoord.setX(avatarCoord.getX() - this->map->getX());
        avatarCoord.setY(avatarCoord.getY() - this->map->getY());
    }
    if (this->numBullets < this->ammoLimit) {
        this->numBullets += 1;
        auto bullet = new Bullet(avatarCoord, 800, this->angleShip, "bullet", this->textureManager, this->map);
        bullet->setXof(this->map->getX());
        bullet->setYof(this->map->getY());
        objects.push_back(bullet);
    } else {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if (dynamic_cast<Bullet*>(*it)) {
                delete (*it);
                objects.erase(it);
                auto bullet = new Bullet(avatarCoord, 800, this->angleShip, "bullet", this->textureManager, this->map);
                bullet->setXof(this->map->getX());
                bullet->setYof(this->map->getY());
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

Reticle::Reticle(std::string textureID, TextureManager* textureManager, Map *map): MovableGameObject(Vector2D{0, 0}, 0, 0, textureID, textureManager, map) {
    this->xOf = this->wSprite / 2;
    this->yOf = this->hSprite / 2;
}

void Reticle::render() const {
    int x = this->coord.getX() - this->xOf;
    int y = this->coord.getY() - this->yOf;
    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite);
}