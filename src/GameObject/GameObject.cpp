#include "GameObject.h"

GameObject::GameObject(Vector2D coord, std::string& textureID, TextureManager* textureManager) {
    this->hSprite = 0;
    this->wSprite = 0;
    this->textureManager = textureManager;
    this->textureID = textureID;
    textureManager->getTextureSize(textureID,this->wSprite,this->hSprite);
    this->coord = coord;
}

void GameObject::setX(double x) {
    this->coord.setX(x);
}
void GameObject::setY(double y) {
    this->coord.setY(y);
}

double GameObject::getX() const {
    return this->coord.getX();
}

double GameObject::getY() const {
    return this->coord.getY();
}

void GameObject::render() {
    this->textureManager->draw(this->textureID,this->coord.getX(),this->coord.getY(),this->wSprite,this->hSprite);
}

