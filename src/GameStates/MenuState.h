//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>

#include "PlayState.h"
#include "../GameObject/Button/Button.h"
#include "../GameWindow/GameWindow.h"

class MenuState : public GameState {
private:
    GameWindow* gameWindow;
    static const std::string menuID;
    std::vector<Button*> menuButtons;
public:
    MenuState(GameWindow* gameWindow);
    ~MenuState() override;
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

};
