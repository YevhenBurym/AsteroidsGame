//
// Created by Евгений on 20.07.2022.
//

#include "StateMachine.h"

StateMachine::StateMachine() {
    this->isChange = false;
    this->needToDelete = nullptr;
}

void StateMachine::pushState(GameState *pState) {
    this->gameStates.push_back(pState);
}

void StateMachine::popState() {
    if (!this->gameStates.empty()) {
        this->needToDelete = this->gameStates.back();
        this->isChange = true;
        this->gameStates.pop_back();
    }
}

void StateMachine::changeState(GameState *pState) {
    if (!this->gameStates.empty()) {
        if (this->gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }
        this->needToDelete = this->gameStates.back();
        this->isChange = true;
        this->gameStates.pop_back();
    }
    this->gameStates.push_back(pState);
}

void StateMachine::update() {
    if (!this->gameStates.empty()) {
        this->gameStates.back()->update();
    }
}

void StateMachine::render() {
    if (!this->gameStates.empty()) {
        this->gameStates.back()->render();
    }
}

bool StateMachine::needToErasePrevState() {
    if (this->isChange) {
        delete this->needToDelete;
        this->needToDelete = nullptr;
        this->isChange = false;
        return true;
    }
    return false;
}