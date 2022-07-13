//
// Created by Евгений on 07.07.2022.
//

#include "InputComponent.h"

InputComponent::InputComponent(Game* game) {
    this->game = game;
}

void InputComponent::handleInput(SDL_Event& event) {
    //If a key was pressed
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
        this->onKeyPressed(event.key.keysym.sym);
    //If a key was released
    } else if( event.type == SDL_KEYUP && event.key.repeat == 0 ) {
        this->onKeyReleased(event.key.keysym.sym);
    }

    if (event.type == SDL_MOUSEMOTION) {
        this->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
        event.motion.state = SDL_RELEASED;      // если не ставить, то при движении мыши ставит event.button.state == SDL_RELEASED
    }

    if( event.type == SDL_MOUSEBUTTONDOWN ) {
        this->onMouseButtonPressed(event.button.button);

    } else if( event.type == SDL_MOUSEBUTTONUP ) {
        this->onMouseButtonReleased(event.button.button);
    }

}

void InputComponent::onKeyPressed(SDL_Keycode key) {
    int V = 300;

    switch( key ) {
        case SDLK_UP:
            this->game->getMap()->setV(V, 270);
            //this->game->getMap()->setVx(10);
            break;
        case SDLK_DOWN:
            this->game->getMap()->setV(V, 90);
            //this->game->getMap()->setVx(10);
            break;
        case SDLK_LEFT:
            this->game->getMap()->setV(V, 0);
            //this->game->getMap()->setVx(10);
            break;
        case SDLK_RIGHT:
            this->game->getMap()->setV(V, 180);
            //this->game->getMap()->setVx(10);
            break;
        default:
            break;
    }
}

void InputComponent::onKeyReleased(SDL_Keycode key) {
    switch( key ) {
        case SDLK_UP:
            this->game->getMap()->setIsNeededDeacc(true);
            break;
        case SDLK_DOWN:
            this->game->getMap()->setIsNeededDeacc(true);
            break;
        case SDLK_LEFT:
            this->game->getMap()->setIsNeededDeacc(true);
            break;
        case SDLK_RIGHT:
            this->game->getMap()->setIsNeededDeacc(true);
            break;
        default:
            break;
    }
}

void InputComponent::onMouseButtonPressed(int MouseButton) {
    switch (MouseButton) {
        case SDL_BUTTON_LEFT:

            break;
        case SDL_BUTTON_MIDDLE:

            break;
        case SDL_BUTTON_RIGHT:

            break;
        default:
            break;
    }
}

void InputComponent::onMouseButtonReleased(int MouseButton) {
    switch (MouseButton) {
        case SDL_BUTTON_LEFT:
            this->game->getAvatar()->makeShoot(this->game->getObjects());
            break;
        case SDL_BUTTON_MIDDLE:

            break;
        case SDL_BUTTON_RIGHT:

            break;
        default:
            break;
    }
}

void InputComponent::onMouseMove(int x, int y, int xrelative, int yrelative) {
    this->game->getAvatar()->getReticle()->setX(x);
    this->game->getAvatar()->getReticle()->setY(y);
}


