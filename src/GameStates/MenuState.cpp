//
// Created by Евгений on 20.07.2022.
//

#include "MenuState.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update()
{
    for(int i = 0; i < this->menuButtons.size(); i++) {
        this->menuButtons[i]->update();
    }
}
void MenuState::render()
{
    for(int i = 0; i < this->menuButtons.size(); i++) {
        this->menuButtons[i]->render();
    }
}

bool MenuState::onEnter()
{
    auto playButton = new Button({220,100},"start_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(),[this]() { s_menuToPlay(); });
    auto exitButton = new Button({220,300},"exit_button",this->gameWindow->getTextureManager(),this->gameWindow->getInputHadler(),[this]() { s_exitFromMenu(); });
    this->menuButtons.push_back(playButton);
    this->menuButtons.push_back(exitButton);
    SDL_ShowCursor(SDL_ENABLE);

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
//    for(auto & menuButton : this->menuButtons) {
//        delete menuButton;
//    }
//    this->menuButtons.clear();
    for (auto it = this->menuButtons.begin(); it != this->menuButtons.end();) {
        delete (*it++);
    }
    this->menuButtons.clear();
    this->menuButtons.shrink_to_fit();

    std::cout << "exiting MenuState\n";
    return true;
}

MenuState::MenuState(GameWindow* gameWindow) {
    this->gameWindow = gameWindow;
}

void MenuState::s_menuToPlay() {
    this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow));
}

void MenuState::s_exitFromMenu() {
    this->gameWindow->setFlagQuitGame(true);
}

std::string MenuState::getStateID() const {
    return MenuState::menuID;
}

MenuState::~MenuState() {
}
