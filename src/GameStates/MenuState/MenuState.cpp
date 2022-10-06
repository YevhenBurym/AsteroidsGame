//
// Created by Евгений on 20.07.2022.
//

#include "MenuState.h"

const std::string MenuState::menuID = "MENU";

MenuState::MenuState(GameWindow *gameWindow) {
    this->gameWindow = gameWindow;

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
//    int h,w;
//    this->gameWindow->getTextureManager()->getTextureSize("start_button",w,h);
//    double x = this->gameWindow->getSize().width /2 - w/3;
//    double y = this->gameWindow->getSize().height/2 - h/3;

    auto playButton = new Button({280, 150}, "start_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toPlay);
    auto exitButton = new Button({280, 350}, "exit_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toExit);
    this->menuButtons.push_back(playButton);
    this->menuButtons.push_back(exitButton);

    SDL_ShowCursor(SDL_ENABLE);
}

MenuState::~MenuState() {
    for (auto &menuButton : this->menuButtons) {
        delete menuButton;
    }
    this->menuButtons.clear();
}

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

std::string MenuState::getStateID() const {
    return MenuState::menuID;
}

