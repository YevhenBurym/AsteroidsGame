//
// Created by Евгений on 22.07.2022.
//

#pragma once

#include "GameState.h"
#include "../GameWindow/GameWindow.h"
#include "../InputComponent/InputComponent.h"
#include "../GameObject/Button/Button.h"
#include "MenuState.h"

class PauseState : public GameState {
private:
    GameWindow* gameWindow;
    static const std::string pauseID;
    std::vector<Button *> menuButtons;
public:
    PauseState(GameWindow* gameWindow);
    ~PauseState() override;
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;
};
