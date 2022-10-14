//
// Created by Евгений on 03.10.2022.
//

#include "GameObject.h"

GameObject::GameObject(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager) {
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
    this->radius = d / 2;
    this->xy = coord;
    this->Vxy = Vxy;
    this->mass = 1;
    this->xyOffset = {0,0};
    this->acceleration = {0,0};
}

GameObject::~GameObject() = default;

void GameObject::setXY(Vector2D newXY) {
    this->xy = newXY;
}

Vector2D GameObject::getXY() const {
    return this->xy;
}

void GameObject::setVxy(Vector2D vxy) {
    this->Vxy = vxy;
}

Vector2D GameObject::getXYrel() const {
    Vector2D currXY = this->xy;
    Vector2D xyOf = this->xyOffset;

    return currXY + xyOf;
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
    int x = this->xy.getX() + this->xyOffset.getX() - this->radius;
    int y = this->xy.getY() + this->xyOffset.getY() - this->radius;

    this->textureManager->draw(this->textureID, x, y,this->wSprite,this->hSprite);
}

void GameObject::update() {
    this->xy += this->Vxy;
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

