//
// Created by Евгений on 03.10.2022.
//

#include "GameObject.h"

GameObject::GameObject(Vector2D coord, double velocity, double theta,
                       std::string textureID, TextureManager* textureManager) {
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
    //this->map = map;
    this->radius = d / 2;
    this->coord = coord;
    this->Vxy.setX(velocity * cos(theta * toRad));
    this->Vxy.setY(-velocity * sin(theta * toRad));
    this->mass = 1;
    this->V.v = velocity;
    this->V.theta = theta;
    //this->xOf = this->map->getXY().getX();
    //this->yOf = this->map->getXY().getY();
    this->acceleration = {0,0};
}

GameObject::~GameObject() = default;

void GameObject::calcCoord() {
    this->coord.setX(this->coord.getX() + this->Vxy.getX() * 0.001);
    this->coord.setY(this->coord.getY() + this->Vxy.getY() * 0.001);
}

void GameObject::setXY(Vector2D newXY) {
    this->coord = newXY;
}

Vector2D GameObject::getXY() const {
    return this->coord;
}

void GameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
}

Vector2D GameObject::getXYrel() const {
    return Vector2D{this->coord.getX() + this->xOf, this->coord.getY() + this->yOf};
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

void GameObject::render() {
    int x = this->coord.getX() + this->xOf - this->radius;
    int y = this->coord.getY() + this->yOf - this->radius;

    this->textureManager->draw(this->textureID,x,y,this->wSprite,this->hSprite);
}

void GameObject::update() {
    this->calcCoord();
    //this->xOf = this->map->getXY().getX();
    //this->yOf = this->map->getXY().getY();
}

LimitatorXY::LimitatorXY(Map *map) {
    this->map = map;
}

void LimitatorXY::limitateXY(Vector2D& currXY) {
    if (currXY.getX() >= this->map->getMaxCoord().getX()) {
        currXY.setX(this->map->getMinCoord().getX());
    } else if (currXY.getX() < this->map->getMinCoord().getX()) {
        currXY.setX(this->map->getMaxCoord().getX());
    }

    if (currXY.getY() >= this->map->getMaxCoord().getY()) {
        currXY.setY(this->map->getMinCoord().getY());
    } else	if (currXY.getY() < this->map->getMinCoord().getY()) {
        currXY.setY(this->map->getMaxCoord().getY());
    }
}

