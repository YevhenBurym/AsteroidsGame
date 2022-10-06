//
// Created by Евгений on 22.07.2022.
//

#pragma once

#include "../GameObject/GameOverMessage/GameOverMessage.h"
#include "../InputComponent/InputComponent.h"
#include "../GameObject/Button/Button.h"
#include "PlayState.h"
#include "MenuState.h"

class GameOverState : public GameState {
private:
    GameWindow* gameWindow;
    static const std::string gameOverID;
    std::vector<GameObject *> gameOverObjects;
public:
    GameOverState(GameWindow* gameWindow);
    ~GameOverState() override;
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;


};

