//
// Created by Евгений on 07.07.2022.
//

#include "InputHandler.h"

InputHandler::InputHandler() {
    this->initMouseButtons();
    this->keyStates = SDL_GetKeyboardState(nullptr);
    this->quitGame = false;
}

void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->quitGame = true;
                break;
            case SDL_MOUSEMOTION:
                this->onMouseMove(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                this->onMouseButtonPressed(event);
                break;
            case SDL_MOUSEBUTTONUP:
                this->onMouseButtonReleased(event);
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

void InputHandler::onKeyPressed() {
    this->keyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::onKeyReleased() {
    this->keyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::onMouseButtonPressed(SDL_Event& event) {
    int mouseButton = event.button.button;
    switch (mouseButton) {
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

void InputHandler::onMouseButtonReleased(SDL_Event& event) {
    int mouseButton = event.button.button;
    switch (mouseButton) {
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

void InputHandler::onMouseMove(SDL_Event& event) {
    this->mousePosition.setX(event.motion.x);
    this->mousePosition.setY(event.motion.y);
}

Vector2D InputHandler::getMousePosition() {
    return this->mousePosition;
}

bool InputHandler::getMouseButtonState(int button) {
    return this->mouseButtonStates[button];
}

void InputHandler::initMouseButtons() {
    for (int i = 0; i < 3; i++) {
        this->mouseButtonStates.push_back(false);
    }
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
    if (this->keyStates != nullptr) {
        return this->keyStates[key] == 1;
    }
    return false;
}

bool InputHandler::getFlagQuitGame() const {
    return this->quitGame;
}
