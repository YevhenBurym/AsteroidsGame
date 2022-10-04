//
// Created by Евгений on 20.07.2022.
//

#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *pState) {
    this->gameStates.push_back(pState);
    this->gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    if (!this->gameStates.empty()) {
        if (this->gameStates.back()->onExit()) {
            delete this->gameStates.back();
            this->gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(GameState *pState) {
    if (!this->gameStates.empty()) {
        if (this->gameStates.back()->getStateID() == pState->getStateID()) {
            return; // do nothing
        }
        if (this->gameStates.back()->onExit()) {
            delete this->gameStates.back();
            this->gameStates.pop_back();
        }
    }
    this->gameStates.push_back(pState);
// initialise it
    this->gameStates.back()->onEnter();
}

void GameStateMachine::update() {
    if (!this->gameStates.empty()) {
        this->gameStates.back()->update();
    }
}

void GameStateMachine::render() {
    if (!this->gameStates.empty()) {
        this->gameStates.back()->render();
    }
}