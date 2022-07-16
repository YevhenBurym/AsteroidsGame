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

GameObject::GameObject(Vector2D coord, double velocity, double theta, Sprite* sprite, Map* map) {
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
    this->Vxy.x = velocity * cos(theta * RAD);
    this->Vxy.y = -velocity * sin(theta * RAD);
    this->sprite = sprite;
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
}

void GameObject::calcCoord(Vector2D Vxy, double step) {
    this->coord.x += Vxy.x * step;
    this->coord.y += Vxy.y * step;
    this->limitateCoord();

}

void GameObject::setX(double x) {
    this->coord.x = x;
}
void GameObject::setY(double y) {
    this->coord.y = y;
}

void GameObject::setXof(double x) {
    this->xOf = x;
}

void GameObject::setYof(double y) {
    this->yOf = y;
}

void GameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
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

Vector2D GameObject::getVxy() const {
    return this->Vxy;
}

double GameObject::getMass() const {
    return this->mass;
}

double GameObject::getRadius() const {
    return this->radius;
}

void GameObject::render() const {

    int x = this->coord.x + this->xOf - this->radius;
    int y = this->coord.y + this->yOf - this->radius;

    this->sprite->draw(x, y);
}

