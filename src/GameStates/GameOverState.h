//
// Created by Евгений on 22.07.2022.
//

#pragma once

#include "../GameObject/GameOverMessage.h"
#include "../InputComponent/InputComponent.h"
#include "../GameObject/Button.h"
#include "PlayState.h"
#include "MenuState.h"

class GameOverState : public GameState {
public:
    GameOverState(GameWindow* gameWindow);
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    GameWindow* gameWindow;
    void s_gameOverToMain();
    void s_restartPlay();
    static const std::string gameOverID;
    std::vector<GameObject *> gameOverObjects;
};

