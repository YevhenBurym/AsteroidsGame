//
// Created by Евгений on 20.07.2022.
//

#include "MenuState.h"

const std::string MenuState::menuID = "MENU";

void MenuState::update()
{
    for(int i = 0; i < this->menuButtons.size(); i++)
    {
        this->menuButtons[i]->update();
    }
}
void MenuState::render()
{
    for(int i = 0; i < this->menuButtons.size(); i++)
    {
        this->menuButtons[i]->render();
    }
}

bool MenuState::onEnter()
{
    auto playButton = new Button({220,100},"play_button",this->gameWindow->getTextureManager(),this->inputComponent,[this]() { s_menuToPlay(); });
    auto exitButton = new Button({220,300},"exit_button",this->gameWindow->getTextureManager(),this->inputComponent,[this]() { s_exitFromMenu(); });
    //GameObject* button1 = new Button(new LoaderParams(220, 100,208, 84, "playbutton",game->getTextureManager()),game->getInputHandler(),[this]() { s_menuToPlay(); });
    //GameObject* button2 = new Button(new LoaderParams(220, 300,208, 84, "exitbutton",game->getTextureManager()),game->getInputHandler(), [this]() { s_exitFromMenu(); });
    this->menuButtons.push_back(playButton);
    this->menuButtons.push_back(exitButton);
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for(auto & menuButton : this->menuButtons)
    {
        delete menuButton;
    }
    this->menuButtons.clear();
    std::cout << "exiting MenuState\n";
    return true;
}

MenuState::MenuState(GameWindow* gameWindow, InputComponent* inputComponent) {
    this->gameWindow = gameWindow;
    this->inputComponent = inputComponent;
}

void MenuState::s_menuToPlay() {
    this->gameWindow->getGameStateMachine()->changeState(new PlayState(this->gameWindow,this->inputComponent));
}

void MenuState::s_exitFromMenu() {
    this->gameWindow->setFlagQuitGame(true);
}

std::string MenuState::getStateID() const {
    return MenuState::menuID;
}