#include "GameObject.h"
#include <cmath>

void GameObject::limitateCoord() {
    double minXCoord = 0 - map->getMapOffsetCoord().x;
    double maxXCoord = map->getWMap() - map->getMapOffsetCoord().x;
    double minYCoord = 0 - map->getMapOffsetCoord().y;
    double maxYCoord = map->getHMap() - map->getMapOffsetCoord().y;

    if (this->coord.x >= maxXCoord) {
        this->coord.x = minXCoord;
    } else if (this->coord.x < minXCoord) {
        this->coord.x = maxXCoord;
    }

    if (this->coord.y >= maxYCoord) {
        this->coord.y = minYCoord;
    } else	if (this->coord.y < minYCoord) {
        this->coord.y = maxYCoord;
    }
}

GameObject::GameObject(CoordXY coord, double velocity, double theta, Sprite* sprite, Map* map) {
    CoordXY CoordOffset = map->getMapOffsetCoord();
    int wSprite, hSprite;
    double d = 0;
    //theta *= -1;
    sprite->getSize(wSprite,hSprite);

    if (wSprite % hSprite == wSprite) {
        d = hSprite - (hSprite % wSprite) / 2;
    } else {
        d = wSprite - (wSprite % hSprite) / 2;
    }
    this->map = map;
    this->radius = d / 2;
    this->coord = coord;
    this->Vx = velocity * cos(theta * RAD);
    this->Vy = -velocity * sin(theta * RAD);
    this->sprite = sprite;
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
}

void GameObject::calcCoord(double Vx, double Vy, double step) {
    this->coord.x += Vx * step;
    this->coord.y += Vy * step;
    this->limitateCoord();

}

void GameObject::setX(double x) {
    this->coord.x = x;
}
void GameObject::setY(double y) {
    this->coord.y = y;
}

void GameObject::setXof(double x){
    this->xOf = x;
}

void GameObject::setYof(double y) {
    this->yOf = y;
}

void GameObject::setVx(double vx) {
    this->Vx = vx;
}
void GameObject::setVy(double vy) {
    this->Vy = vy;
}

void GameObject::setV(double v, double theta) {
    this->V.v = v;
    this->V.theta = theta;
    this->Vx = v * cos(theta * RAD);
    this->Vy = -v * sin(theta * RAD);
}

double GameObject::getX() const {
    return this->coord.x;
}

double GameObject::getY() const {
    return this->coord.y;
}

double GameObject::getXrel() const {
    return this->coord.x + this->xOf;
}
double GameObject::getYrel() const {
    return this->coord.y + this->yOf;
}

double GameObject::getVx() const {
    return this->Vx;
}

double GameObject::getVy() const {
    return this->Vy;
}

Velocity GameObject::getV() const {
    return this->V;
}

double GameObject::getMass() const {
    return this->mass;
}

double GameObject::getRadius() const {
    return this->radius;
}

Sprite* GameObject::getSprite() const {
    return this->sprite;
}

void GameObject::draw() const {
    this->sprite->draw(this->coord.x, this->coord.y);
}

SmallAsteroid::SmallAsteroid(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
    this->mass = 1;
}

BigAsteroid::BigAsteroid(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
    this->mass = 2;
}

//SmallAsteroid* BigAsteroid::divide() {
//    MoveableUnit* temp = this;
//    this = new SmallAsteroid();
//}

void Avatar::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().x;
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().x;
    double minYCoord = 0 - this->map->getMapOffsetCoord().y;
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().y;
    double x = this->coord.x + this->xOf;
    double y = this->coord.y + this->yOf;

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

Avatar::Avatar(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
}

double Avatar::getXrel() const {
    return this->coord.x;
}

double Avatar::getYrel() const {
    return this->coord.y;
}

Bullet::Bullet(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map) : GameObject(coord, velocity, theta, sprite, map) {
}

Reticle::Reticle(Sprite *sprite, Map *map): GameObject(CoordXY{0,0}, 0, 0, sprite, map) {
    int wSprite, hSprite;
    this->sprite->getSize(wSprite, hSprite);
    this->xOf = wSprite / 2;
    this->yOf = hSprite / 2;
}

void Reticle::draw() const {
    int x = this->coord.x - this->xOf;
    int y = this->coord.y - this->yOf;
    this->sprite->draw(x,y);
}
