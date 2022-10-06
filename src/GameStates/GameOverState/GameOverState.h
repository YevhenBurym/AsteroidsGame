//
// Created by Евгений on 22.07.2022.
//

#pragma once

#include "../../GameObject/GameOverMessage/GameOverMessage.h"
#include "../../GameObject/Button/Button.h"
#include "../MenuState/MenuState.h"
#include "../PlayState/PlayState.h"

class GameOverState : public GameState {
private:
    GameWindow* gameWindow;
    std::vector<GameObject *> gameOverObjects;
    static const std::string gameOverID;
public:
    GameOverState(GameWindow* gameWindow);
    ~GameOverState() override;
    void update() override;
    void render() override;
    std::string getStateID() const override;


};

