//
// Created by Евгений on 03.10.2022.
//

#include "Button.h"

void Button::render() const {
    this->textureManager->drawFrame(this->textureID, this->coord.getX(),this->coord.getY(),this->wSprite, this->hSprite,0, this->m_currentFrame);
}

Button::Button(Vector2D coord, std::string textureID, TextureManager *textureManager, InputComponent *inputComponent,
               std::function<void()> callback):GameObject(coord, textureID, textureManager) {
    this->inputComponent = inputComponent;
    this->m_currentFrame = MOUSE_OUT;
    this->m_bReleased = false;
}

void Button::update() {
    Vector2D mousePos = this->inputComponent->getMousePosition();
    if(mousePos.getX() < (this->coord.getX() + this->wSprite)
       && mousePos.getX() > this->coord.getX()
       && mousePos.getY() < (this->coord.getY() + this->hSprite)
       && mousePos.getY() > this->coord.getY())
    {
        if(this->inputComponent->getMouseButtonState(LEFT) && this->m_bReleased) {
            //this->m_currentFrame = CLICKED;
            this->m_callback(); // call our callback function
            this->m_bReleased = false;
        } else if (!this->inputComponent->getMouseButtonState(LEFT)) {
            this->m_bReleased = true;
            this->m_currentFrame = MOUSE_OVER;
        }
    } else {
        this->m_currentFrame = MOUSE_OUT;
    }
}
