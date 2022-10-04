//
// Created by Евгений on 03.10.2022.
//

#include "GameOverMessage.h"

GameOverMessage::GameOverMessage(Vector2D coord, std::string textureID, TextureManager* textureManager, int animSpeed) : GameObject(coord,textureID, textureManager) {
    this->wSprite /= 2;
    this->animationSpeed = animSpeed;
}

void GameOverMessage::update() {
    this->currentFrame = int(((SDL_GetTicks() / (1000 / this->animationSpeed)) % 2));
}

void GameOverMessage::render(SDL_Renderer *pRenderer) {
    this->textureManager->drawFrame(this->textureID, this->coord.getX(),this->coord.getY(),this->wSprite, this->hSprite,0, this->currentFrame);
}