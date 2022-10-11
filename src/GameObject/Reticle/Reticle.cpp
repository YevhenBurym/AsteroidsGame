//
// Created by Евгений on 06.10.2022.
//

#include "Reticle.h"

Reticle::Reticle(std::string textureID, TextureManager *textureManager) : GameObject(Vector2D{0, 0}, 0, 0, textureID,
                                                                                     textureManager) {}

void Reticle::render() {
    int x = this->coord.getX() - this->radius;
    int y = this->coord.getY() - this->radius;
    this->textureManager->draw(this->textureID, x, y, this->wSprite, this->hSprite);
}
