#include "GameObject.h"

GameObject::GameObject(Vector2D coord, std::string& textureID, TextureManager* textureManager) {
    this->hSprite = 0;
    this->wSprite = 0;
    this->textureManager = textureManager;
    this->textureID = textureID;
    textureManager->getTextureSize(textureID,this->wSprite,this->hSprite);
    this->coord = coord;
}

void GameObject::setXY(Vector2D newXY) {
   this->coord = newXY;
}

Vector2D GameObject::getXY() const {
   return this->coord;
}

void GameObject::render() {
    this->textureManager->draw(this->textureID,this->coord.getX(),this->coord.getY(),this->wSprite,this->hSprite);
}

