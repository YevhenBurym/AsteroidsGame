//
// Created by Евгений on 03.10.2022.
//

#include "Button.h"

void Button::render() {
    this->textureManager->drawFrame(this->textureID, this->coord.getX(),this->coord.getY(),this->wSprite, this->hSprite,1, this->currentFrame);
}

Button::Button(Vector2D coord, std::string textureID, TextureManager *textureManager, InputHandler *inputHandler,
               std::function<void()>& callbackFunction): GameObject(coord, 0, 0, textureID, textureManager) {
    this->callbackFunction = callbackFunction;
    this->wSprite /= 2;
    this->inputHandler = inputHandler;
    this->currentFrame = MOUSE_OUT;
    this->isButtonReleased = false;
}

void Button::update() {
    Vector2D mousePos = this->inputHandler->getMousePosition();
    if(mousePos.getX() < (this->coord.getX() + this->wSprite)
       && mousePos.getX() > this->coord.getX()
       && mousePos.getY() < (this->coord.getY() + this->hSprite)
       && mousePos.getY() > this->coord.getY())
    {
        if(this->inputHandler->getMouseButtonState(LEFT) && this->isButtonReleased) {
            this->callbackFunction();
            this->isButtonReleased = false;
        } else if (!this->inputHandler->getMouseButtonState(LEFT)) {
            this->isButtonReleased = true;
            this->currentFrame = MOUSE_OVER;
        }
    } else {
        this->currentFrame = MOUSE_OUT;
    }
}
