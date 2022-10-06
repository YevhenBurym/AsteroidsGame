//
// Created by Евгений on 20.07.2022.
//

#include "MenuState.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update() {
    for (auto menuButton : this->menuButtons) {
        menuButton->update();
        if (this->gameWindow->getGameStateMachine()->needToErasePrevState()) {
            return;
        };
    }
}

void MenuState::render() {
    for (auto &menuButton : this->menuButtons) {
        menuButton->render();
    }
}

bool MenuState::onEnter() {
//    int h,w;
//    this->gameWindow->getTextureManager()->getTextureSize("start_button",w,h);
//    double x = this->gameWindow->getSize().width /2 - w/3;
//    double y = this->gameWindow->getSize().height/2 - h/3;
    SDL_ShowCursor(SDL_ENABLE);
    std::function<void()> toPlay{
            [this]() {
                this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow));
            }
    };

    std::function<void()> toExit{
            [this]() {
                this->gameWindow->setFlagQuitGame(true);
            }
    };

    auto playButton = new Button({280, 150}, "start_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toPlay);
    auto exitButton = new Button({280, 350}, "exit_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toExit);
    this->menuButtons.push_back(playButton);
    this->menuButtons.push_back(exitButton);
    return true;
}

bool MenuState::onExit() {
    return true;
}

MenuState::MenuState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;
}

std::string MenuState::getStateID() const {
    return MenuState::menuID;
}

MenuState::~MenuState() {
    for (auto &menuButton : this->menuButtons) {
        delete menuButton;
    }
    this->menuButtons.clear();
}