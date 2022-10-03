//
// Created by Евгений on 03.10.2022.
//

#include "MovableGameObject.h"

void MovableGameObject::limitateCoord() {
    double minXCoord = 0 - this->map->getMapOffsetCoord().getX();
    double maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().getX();
    double minYCoord = 0 - this->map->getMapOffsetCoord().getY();
    double maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().getY();

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

MovableGameObject::MovableGameObject(Vector2D coord, double velocity, double theta, std::string textureID, TextureManager* textureManager, Map* map): GameObject(coord, textureID, textureManager) {
    double d;
    this->hSprite = 0;
    this->wSprite = 0;
    this->textureManager = textureManager;
    this->textureID = textureID;
    textureManager->getTextureSize(textureID,this->wSprite,this->hSprite);

    if (this->wSprite % this->hSprite == this->wSprite) {
        d = this->hSprite - (this->hSprite % this->wSprite) / 2;
    } else {
        d = this->wSprite - (this->wSprite % this->hSprite) / 2;
    }
    this->map = map;
    this->radius = d / 2;
    this->coord = coord;
    this->Vxy.setX(velocity * cos(theta * RAD));
    this->Vxy.setY(-velocity * sin(theta * RAD));
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = 0;
    this->yOf = 0;
    this->acceleration = {0,0};
}

void MovableGameObject::calcCoord(Vector2D Vxy, double step) {
    this->coord.setX(this->coord.getX() + Vxy.getX() * step);
    this->coord.setY(this->coord.getY() + Vxy.getY() * step);
    this->limitateCoord();

}

void MovableGameObject::setXof(double x) {
    this->xOf = x;
}

void MovableGameObject::setYof(double y) {
    this->yOf = y;
}

void MovableGameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
}

double MovableGameObject::getXrel() const {
    return this->coord.getX() + this->xOf;
}
double MovableGameObject::getYrel() const {
    return this->coord.getY() + this->yOf;
}

Vector2D MovableGameObject::getVxy() const {
    return this->Vxy;
}

double MovableGameObject::getMass() const {
    return this->mass;
}

double MovableGameObject::getRadius() const {
    return this->radius;
}

void MovableGameObject::render() const {
    int x = this->coord.getX() + this->xOf - this->radius;
    int y = this->coord.getY() + this->yOf - this->radius;

    this->textureManager->draw(this->textureID,x,y,this->wSprite,this->hSprite);
}

