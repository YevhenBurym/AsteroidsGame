#include "GameObject.h"

void GameObject::limitateCoord() {
    double minXCoord = 0 - map->getMapOffsetCoord().getX();
    double maxXCoord = map->getWMap() - map->getMapOffsetCoord().getX();
    double minYCoord = 0 - map->getMapOffsetCoord().getY();
    double maxYCoord = map->getHMap() - map->getMapOffsetCoord().getY();

    if (this->coord.getX() >= maxXCoord) {
        this->coord.setX(minXCoord);
    } else if (this->coord.getX() < minXCoord) {
        this->coord.setX(maxXCoord);
    }

    if (this->coord.getY() >= maxYCoord) {
        this->coord.setY(minYCoord);
    } else	if (this->coord.getY() < minYCoord) {
        this->coord.setY(maxYCoord);
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
    this->Vxy.setX(velocity * cos(theta * RAD));
    this->Vxy.setY(-velocity * sin(theta * RAD));
    this->sprite = sprite;
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
    this->acceleration = {0,0};
}

void GameObject::calcCoord(Vector2D Vxy, double step) {
    this->coord.setX(this->coord.getX() + Vxy.getX() * step);
    this->coord.setY(this->coord.getY() + Vxy.getY() * step);
    this->limitateCoord();

}

void GameObject::setX(double x) {
    this->coord.setX(x);
}
void GameObject::setY(double y) {
    this->coord.setY(y);
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
    return this->coord.getX();
}

double GameObject::getY() const {
    return this->coord.getY();
}

double GameObject::getXrel() const {
    return this->coord.getX() + this->xOf;
}
double GameObject::getYrel() const {
    return this->coord.getY() + this->yOf;
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

    int x = this->coord.getX() + this->xOf - this->radius;
    int y = this->coord.getY() + this->yOf - this->radius;

    this->sprite->draw(x, y);
}

