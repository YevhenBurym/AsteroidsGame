//
// Created by Евгений on 03.10.2022.
//

#include "GameOverMessage.h"

GameOverMessage::GameOverMessage(Vector2D coord, std::string textureID, TextureManager* textureManager, int animSpeed) : GameObject(coord,textureID, textureManager) {
    this->wSprite /= 2;
    this->animationSpeed = animSpeed;
    this->currentFrame = 1;
}

void GameOverMessage::update() {
    this->currentFrame = int(((SDL_GetTicks() / (1000 / this->animationSpeed)) % 2));
}

void GameOverMessage::render() {
    this->textureManager->drawFrame(this->textureID, this->coord.getX(),this->coord.getY(),this->wSprite, this->hSprite,1, this->currentFrame);
}