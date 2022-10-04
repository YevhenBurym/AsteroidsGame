//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "../GameObject/Button.h"

class PlayState : public GameState {
private:
    static const std::string playID;
    std::vector<Button *> m_gameObjects;
    GameWindow* gameWindow;
    InputComponent* inputComponent;
public:
    PlayState(GameWindow* gameWindow, InputComponent* inputComponent);
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;
    //bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);
};

