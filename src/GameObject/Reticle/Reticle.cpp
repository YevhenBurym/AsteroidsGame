//
// Created by Евгений on 06.10.2022.
//

#include "Reticle.h"

Reticle::Reticle(std::string textureID, TextureManager *textureManager) : GameObject({0, 0}, {0, 0}, textureID,
                                                                                     textureManager) {}

void Reticle::render() {
    int x = this->xy.getX() - this->radius;
    int y = this->xy.getY() - this->radius;
    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite);
}
