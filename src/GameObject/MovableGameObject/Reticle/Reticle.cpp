//
// Created by Евгений on 06.10.2022.
//

#include "Reticle.h"

Reticle::Reticle(std::string textureID, TextureManager* textureManager, Map *map): MovableGameObject(Vector2D{0, 0}, 0, 0, textureID, textureManager, map) {
    this->xOf = this->wSprite / 2;
    this->yOf = this->hSprite / 2;
}

void Reticle::render() const {
    int x = this->coord.getX() - this->xOf;
    int y = this->coord.getY() - this->yOf;
    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite);
}