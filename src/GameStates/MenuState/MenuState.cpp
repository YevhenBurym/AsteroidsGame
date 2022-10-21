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
    double xStart = this->gameWindow->getSize().width / 2 - wStart / 4;
    double yStart = 2 * this->gameWindow->getSize().height / 5 - hStart / 2;
    double xExit = this->gameWindow->getSize().width / 2 - wExit / 4;
    double yExit = 3 * this->gameWindow->getSize().height / 5 - hExit / 2;

    int hTitle,wTitle;
    this->gameTitle = new MessageString("stencil", "simple asteroids", "game_title", this->gameWindow->getTextureManager());
    this->gameWindow->getTextureManager()->getTextureSize("game_title",wTitle, hTitle);
    double xTitle = this->gameWindow->getSize().width / 2 - wTitle / 2;
    double yTitle = this->gameWindow->getSize().height / 5 - hTitle / 2;
    this->gameTitle->setXY({xTitle,yTitle});

    int h1,w1;
    this->instruction = new MessageString("inkfree", "How to play: arrows - to move, lmb - to shoot, rmb - to activate ability", "instruction", this->gameWindow->getTextureManager());
    this->gameWindow->getTextureManager()->getTextureSize("instruction",w1, h1);
    double x1 = this->gameWindow->getSize().width / 2 - w1 / 2;
    double y1 = 4 * this->gameWindow->getSize().height / 5 - h1 / 2;
    this->instruction->setXY({x1,y1});




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
    this->gameWindow->getTextureManager()->clearFromTextureMap("game_title");
    this->gameWindow->getTextureManager()->clearFromTextureMap("instruction");
    delete this->gameTitle;
    delete this->instruction;
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
    this->gameTitle->render();
    this->instruction->render();
}

std::string MenuState::getStateID() const {
    return MenuState::menuID;
}

