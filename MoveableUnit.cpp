#include "MoveableUnit.h"
#include <cmath>

void MoveableUnit::limitateCoord() {
    double minXCoord = 0 - map->getMapOffsetCoord().x;
    double maxXCoord = map->getWMap() - map->getMapOffsetCoord().x;
    double minYCoord = 0 - map->getMapOffsetCoord().y;
    double maxYCoord = map->getHMap() - map->getMapOffsetCoord().y;

    if (this->x >= maxXCoord) {
        this->x = minXCoord;
    } else if (this->x < minXCoord) {
        this->x = maxXCoord;
    }

    if (this->y >= maxYCoord) {
        this->y = minYCoord;
    } else	if (this->y < minYCoord) {
        this->y = maxYCoord;
    }
}

MoveableUnit::MoveableUnit(double x, double y, double velocity, double theta, Sprite* sprite, Map* map) {
    CoordXY CoordOffset = map->getMapOffsetCoord();
    int wSprite, hSprite;
    double d = 0;
    //theta *= -1;
    sprite->getSize(wSprite,hSprite);
    //getTextureSize(sprite, wSprite, hSprite);

    if (wSprite % hSprite == wSprite) {
        d = hSprite - (hSprite % wSprite) / 2;
    } else {
        d = wSprite - (wSprite % hSprite) / 2;
    }
    this->map = map;
    this->radius = d / 2;
    this->x = x;
    this->y = y;
    this->Vx = velocity * cos(theta * RAD);
    this->Vy = -velocity * sin(theta * RAD);
    this->sprite = sprite;
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
}

void MoveableUnit::calcCoord(double Vx, double Vy, double step) {
    this->x += Vx * step;
    this->y += Vy * step;
    this->limitateCoord();

}

void MoveableUnit::setX(double x) {
    this->x = x;
}
void MoveableUnit::setY(double y) {
    this->y = y;
}

void MoveableUnit::setXof(double x){
    this->xOf = x;
}

void MoveableUnit::setYof(double y) {
    this->yOf = y;
}

void MoveableUnit::setVx(double vx) {
    this->Vx = vx;
}
void MoveableUnit::setVy(double vy) {
    this->Vy = vy;
}

void MoveableUnit::setV(double v, double theta) {
    this->V.v = v;
    this->V.theta = theta;
    this->Vx = v * cos(theta * RAD);
    this->Vy = -v * sin(theta * RAD);
}

double MoveableUnit::getX() const {
    return this->x;
}

double MoveableUnit::getY() const {
    return this->y;
}

double MoveableUnit::getXrel() const {
    return this->x + this->xOf;
}
double MoveableUnit::getYrel() const {
    return this->y + this->yOf;
}

double MoveableUnit::getVx() const {
    return this->Vx;
}

double MoveableUnit::getVy() const {
    return this->Vy;
}

Velocity MoveableUnit::getV() const {
    return this->V;
}

double MoveableUnit::getMass() const {
    return this->mass;
}

double MoveableUnit::getRadius() const {
    return this->radius;
}

Sprite* MoveableUnit::getSprite() const {
    return this->sprite;
}

SmallAsteroid::SmallAsteroid(double x, double y, int velocity, int theta, Sprite* sprite, Map* map) : MoveableUnit(x, y, velocity, theta, sprite, map) {
    this->mass = 1;
}

BigAsteroid::BigAsteroid(double x, double y, int velocity, int theta, Sprite* sprite, Map* map) : MoveableUnit(x, y, velocity, theta, sprite, map) {
    this->mass = 2;
}

void Avatar::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().x;
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().x;
    double minYCoord = 0 - this->map->getMapOffsetCoord().y;
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().y;
    double x = this->x + this->xOf;
    double y = this->y + this->yOf;

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

Avatar::Avatar(double x, double y, int velocity, int theta, Sprite* sprite, Map* map) : MoveableUnit(x, y, velocity, theta, sprite, map) {
}

double Avatar::getXrel() const {
    return this->x;
}

double Avatar::getYrel() const {
    return this->y;
}

Bullet::Bullet(double x, double y, int velocity, int theta, Sprite* sprite, Map* map) : MoveableUnit(x, y, velocity, theta, sprite, map) {
}
