//
// Created by Евгений on 21.10.2022.
//

#include "MessageString.h"

MessageString::MessageString(Vector2D coord, std::string fontID, std::string text, std::string textureID, TextureManager *textureManager) {
    this->xy = coord;
    this->textureID = textureID;
    this->hSprite = 0;
    this->wSprite = 0;
    this->textureManager = textureManager;
    this->textureManager->createTextureFromText(fontID, text, this->textureID);
    this->textureManager->getTextureSize(this->textureID,this->wSprite,this->hSprite);
}

void MessageString::setXY(Vector2D newXY) {
    this->xy = newXY;
}

Vector2D MessageString::getXY() const {
    return this->xy;
}

void MessageString::render() {
    this->textureManager->draw(this->textureID, this->xy.getX(), this->xy.getY(),this->wSprite,this->hSprite);
}