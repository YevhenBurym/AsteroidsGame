//
// Created by Евгений on 07.07.2022.
//

#include "InputComponent.h"

InputComponent::InputComponent(ObjectManager *objectManager, Map* map) {
    this->objectManager = objectManager;
    this->map = map;
    this->player = dynamic_cast<SpaceShip*>(this->objectManager->getObjects().front());
    this->quitGame = false;
}

void InputComponent::update() {
    //Event handler
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->quitGame = true;
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
            this->map->setVy(1);
            break;
        case SDLK_DOWN:
            this->map->setVy(-1);
            break;
        case SDLK_LEFT:
            this->map->setVx(1);
            break;
        case SDLK_RIGHT:
            this->map->setVx(-1);
            break;
        case SDLK_ESCAPE:
                this->quitGame = true;
            break;
        default:
            break;
    }
}

void InputComponent::onKeyReleased(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            this->map->setIsNeededDeAcc(true);
            break;
        case SDLK_DOWN:
            this->map->setIsNeededDeAcc(true);
            break;
        case SDLK_LEFT:
            this->map->setIsNeededDeAcc(true);
            break;
        case SDLK_RIGHT:
            this->map->setIsNeededDeAcc(true);
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
            this->player->makeShoot(this->objectManager->getObjects());
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
    this->player->getReticle()->setX(x);
    this->player->getReticle()->setY(y);
}

bool InputComponent::getFlagQuitGame() const {
    return quitGame;
}

