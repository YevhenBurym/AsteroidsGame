//
// Created by Евгений on 07.07.2022.
//

#include "InputComponent.h"

InputComponent::InputComponent(Game *game) {
    this->game = game;
}

void InputComponent::update() {
    //Event handler
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->game->setQuit(true);
                break;
            case SDL_MOUSEMOTION:
                this->onMouseMove(event.motion.x, event.motion.y);
                event.motion.state = SDL_RELEASED;      // если не ставить, то при движении мыши ставит event.button.state == SDL_RELEASED
                break;

            case SDL_MOUSEBUTTONDOWN:
                this->onMouseButtonPressed(event.button.button);
                break;

            case SDL_MOUSEBUTTONUP:
                this->onMouseButtonReleased(event.button.button);
                break;

            case SDL_KEYDOWN:
                this->onKeyPressed(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                this->onKeyReleased(event.key.keysym.sym);
                break;

            default:
                break;

        }
    }

}

void InputComponent::onKeyPressed(SDL_Keycode key) {
    switch (key) {
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
        case SDLK_ESCAPE:
            this->game->setQuit(true);
            break;
        default:
            break;
    }
}

void InputComponent::onKeyReleased(SDL_Keycode key) {
    switch (key) {
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


