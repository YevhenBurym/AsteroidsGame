//
// Created by Евгений on 07.07.2022.
//

#include "InputComponent.h"

InputComponent::InputComponent(/*ObjectManager *objectManager*/) {
    this->initMouseButtons();
    this->keyStates = SDL_GetKeyboardState(nullptr);
    //this->objectManager = objectManager;
    //this->player = dynamic_cast<SpaceShip*>(this->objectManager->getObjects().front());
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
                this->onKeyPressed();
                break;
            case SDL_KEYUP:
                this->onKeyReleased();
                break;
            default:
                break;

        }
    }

}

void InputComponent::onKeyPressed() {
    this->keyStates = SDL_GetKeyboardState(nullptr);
}

void InputComponent::onKeyReleased() {
    this->keyStates = SDL_GetKeyboardState(nullptr);
}

void InputComponent::onMouseButtonPressed(int MouseButton) {
    switch (MouseButton) {
        case SDL_BUTTON_LEFT:
                this->mouseButtonStates[LEFT] = true;
            break;
        case SDL_BUTTON_MIDDLE:
                this->mouseButtonStates[MIDDLE] = true;
            break;
        case SDL_BUTTON_RIGHT:
                this->mouseButtonStates[RIGHT] = true;
            break;
        default:
            break;
    }
}

void InputComponent::onMouseButtonReleased(int MouseButton) {
    switch (MouseButton) {
        case SDL_BUTTON_LEFT:
                this->mouseButtonStates[LEFT] = false;
            break;
        case SDL_BUTTON_MIDDLE:
                this->mouseButtonStates[MIDDLE] = false;
            break;
        case SDL_BUTTON_RIGHT:
                this->mouseButtonStates[RIGHT] = false;
            break;
        default:
            break;
    }
}

void InputComponent::onMouseMove(int x, int y) {
    this->mousePosition.setX(x);
    this->mousePosition.setY(y);
}

Vector2D InputComponent::getMousePosition() {
    return this->mousePosition;
}

bool InputComponent::getMouseButtonState(int button) {
    return this->mouseButtonStates[button];
}

void InputComponent::initMouseButtons() {
    for (int i = 0; i < 3; i++) {
        this->mouseButtonStates.push_back(false);
    }
}

bool InputComponent::isKeyDown(SDL_Scancode key) {
    if (this->keyStates != nullptr) {
        return this->keyStates[key] == 1;
    }
    return false;
}

bool InputComponent::getFlagQuitGame() const {
    return this->quitGame;
}
