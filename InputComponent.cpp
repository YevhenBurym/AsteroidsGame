//
// Created by Евгений on 07.07.2022.
//

#include "InputComponent.h"

InputComponent::InputComponent(Game* game) {
    this->game = game;
}

void InputComponent::update() {
    //Event handler
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {

        if (event.type == SDL_QUIT) {
            this->game->setQuit(true);
        }
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_ESCAPE) {
            this->game->setQuit(true);
        }
        //If a key was pressed
        if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            this->onKeyPressed(event.key.keysym.sym);
            //If a key was released
        } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
            this->onKeyReleased(event.key.keysym.sym);
        }

        if (event.type == SDL_MOUSEMOTION) {
            this->onMouseMove(event.motion.x, event.motion.y);
            event.motion.state = SDL_RELEASED;      // если не ставить, то при движении мыши ставит event.button.state == SDL_RELEASED
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            this->onMouseButtonPressed(event.button.button);

        } else if (event.type == SDL_MOUSEBUTTONUP) {
            this->onMouseButtonReleased(event.button.button);
        }
//    switch (event.type) {
//        case SDL_QUIT:
//            SDL_Quit();
//            break;
//
//        case SDL_MOUSEMOTION:
//            //onMouseMove(event);
//            this->onMouseMove(event.motion.x, event.motion.y);
//            event.motion.state = SDL_RELEASED;      // если не ставить, то при движении мыши ставит event.button.state == SDL_RELEASED
//            break;
//
//        case SDL_MOUSEBUTTONDOWN:
//            this->onMouseButtonPressed(event.button.button);
//            //onMouseButtonDown(event);
//            break;
//
//        case SDL_MOUSEBUTTONUP:
//            this->onMouseButtonReleased(event.button.button);
//            //onMouseButtonUp(event);
//            break;
//
//        case SDL_KEYDOWN:
//            this->onKeyPressed(event.key.keysym.sym);
//            //onKeyDown();
//            break;
//
//        case SDL_KEYUP:
//            this->onKeyReleased(event.key.keysym.sym);
//            //onKeyUp();
//            break;
//
//        default:
//            break;
//
//    }
    }

}

void InputComponent::onKeyPressed(SDL_Keycode key) {
    switch( key ) {
        case SDLK_UP:
            this->game->getMap()->setVy(1);
            break;
        case SDLK_DOWN:
            this->game->getMap()->setVy(-1);
            break;
        case SDLK_LEFT:
            this->game->getMap()->setVx(1);
            break;
        case SDLK_RIGHT:
            this->game->getMap()->setVx(-1);
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
            this->game->getPlayer()->makeShoot(this->game->getObjects());
            break;
        case SDL_BUTTON_MIDDLE:

            break;
        case SDL_BUTTON_RIGHT:

            break;
        default:
            break;
    }
}

void InputComponent::onMouseMove(int x, int y) {
    this->game->getPlayer()->getReticle()->setX(x);
    this->game->getPlayer()->getReticle()->setY(y);
}


