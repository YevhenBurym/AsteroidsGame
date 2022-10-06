//
// Created by Евгений on 22.07.2022.
//

#pragma once


#include "../../GameWindow/GameWindow.h"
#include "../../GameObject/Button/Button.h"
#include "../MenuState/MenuState.h"
#include "../GameState.h"

class PauseState : public GameState {
private:
    GameWindow* gameWindow;
    std::vector<Button *> menuButtons;
    static const std::string pauseID;
public:
    PauseState(GameWindow* gameWindow);
    ~PauseState() override;
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;
};
