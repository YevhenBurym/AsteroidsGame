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
    int hStart,wStart;
    int hExit,wExit;
    this->gameWindow->getTextureManager()->getTextureSize("start_button",wStart,hStart);
    this->gameWindow->getTextureManager()->getTextureSize("exit_button",wExit,hExit);
    double xStart = this->gameWindow->getSize().width /2 - wStart / 4;
    double yStart = 2 * this->gameWindow->getSize().height / 5 - hStart / 2;
    double xExit = this->gameWindow->getSize().width / 2 - wExit / 4;
    double yExit = 3 * this->gameWindow->getSize().height / 5 - hExit / 2;

    auto playButton = new Button({xStart, yStart}, "start_button", this->gameWindow->getTextureManager(),
                                 this->gameWindow->getInputHadler(), toPlay);
    auto exitButton = new Button({xExit, yExit}, "exit_button", this->gameWindow->getTextureManager(),
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

