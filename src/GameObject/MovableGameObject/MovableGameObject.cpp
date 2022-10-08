//
// Created by Евгений on 03.10.2022.
//

#include "MovableGameObject.h"

void MovableGameObject::limitateCoord() {
    if (this->coord.getX() >= this->map->getMaxCoord().getX()) {
        this->coord.setX(this->map->getMinCoord().getX());
    } else if (this->coord.getX() < this->map->getMinCoord().getX()) {
        this->coord.setX(this->map->getMaxCoord().getX());
    }

    if (this->coord.getY() >= this->map->getMaxCoord().getY()) {
        this->coord.setY(this->map->getMinCoord().getY());
    } else	if (this->coord.getY() < this->map->getMinCoord().getY()) {
        this->coord.setY(this->map->getMaxCoord().getY());
    }
}

MovableGameObject::MovableGameObject(Vector2D coord, double velocity, double theta,
        std::string textureID, TextureManager* textureManager, Map* map): GameObject(coord, textureID, textureManager) {
    double toRad = M_PI / 180;
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
    this->Vxy.setX(velocity * cos(theta * toRad));
    this->Vxy.setY(-velocity * sin(theta * toRad));
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
    this->acceleration = {0,0};
}

void MovableGameObject::calcCoord() {
    this->coord.setX(this->coord.getX() + this->Vxy.getX() * 0.001);
    this->coord.setY(this->coord.getY() + this->Vxy.getY() * 0.001);
    this->limitateCoord();
}

void MovableGameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
}

Vector2D MovableGameObject::getXYrel() const {
    return Vector2D{this->coord.getX() + this->xOf, this->coord.getY() + this->yOf};
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

void MovableGameObject::update() {
    this->calcCoord();
    this->xOf = this->map->getXY().getX();
    this->yOf = this->map->getXY().getY();
}