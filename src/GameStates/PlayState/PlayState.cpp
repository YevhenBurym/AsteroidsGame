//
// Created by Евгений on 20.07.2022.
//

#include "PlayState.h"

const std::string PlayState::playID = "PLAY";

PlayState::PlayState(GameWindow* gameWindow) {
    this->gameWindow = gameWindow;
    this->objectManager = new ObjectManager(this->gameWindow);
    this->collisions = new Collisions(this->objectManager);
    SDL_ShowCursor(SDL_DISABLE);
}

PlayState::~PlayState() {
   delete this->objectManager;
   delete this->collisions;
}

void PlayState::update() {
    this->gameWindow->getInputHadler()->update();
    if (this->gameWindow->getInputHadler()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        this->gameWindow->getGameStateMachine()->pushState(new PauseState(this->gameWindow));
    }
    this->objectManager->update();
    try {
        this->collisions->update();
    } catch (YouDied) {
        this->gameWindow->getGameStateMachine()->changeState(new GameOverState(this->gameWindow));
        if (this->gameWindow->getGameStateMachine()->needToErasePrevState()) {
            return;
        };
    }
}

void PlayState::render() {
    this->objectManager->render();
}

std::string PlayState::getStateID() const {
    return PlayState::playID;
}

