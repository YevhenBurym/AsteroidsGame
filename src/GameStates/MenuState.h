//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>

#include "PlayState.h"
#include "../GameObject/Button.h"
#include "../GameWindow/GameWindow.h"

class MenuState : public GameState {
private:
    GameWindow* gameWindow;
    InputComponent* inputComponent;
    static const std::string menuID;
    std::vector<Button*> menuButtons;
    // call back functions for menu items
    void s_menuToPlay();
    void s_exitFromMenu();
public:
    MenuState(GameWindow* gameWindow, InputComponent* inputComponent);
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

};
