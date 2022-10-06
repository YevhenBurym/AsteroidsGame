//
// Created by Евгений on 20.07.2022.
//

#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() {
    this->isChange = false;
    this->needToDelete = nullptr;
}

void GameStateMachine::pushState(GameState *pState) {
    this->gameStates.push_back(pState);
    this->gameStates.back()->onEnter();
}

void GameStateMachine::popState() {
    if (!this->gameStates.empty()) {
        if (this->gameStates.back()->onExit()) {
            this->needToDelete = this->gameStates.back();
            this->isChange = true;
            this->gameStates.pop_back();
        }
    }
}

void GameStateMachine::changeState(GameState *pState) {
    if (!this->gameStates.empty()) {
        if (this->gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }
        if (this->gameStates.back()->onExit()) {
            this->needToDelete = this->gameStates.back();
            this->isChange = true;
            this->gameStates.pop_back();
        }
    }
    this->gameStates.push_back(pState);
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

bool GameStateMachine::needToErasePrevState() {
    if (this->isChange) {
        delete this->needToDelete;
        this->needToDelete = nullptr;
        this->isChange = false;
        return true;
    }
    return false;
}