//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "../GameState.h"
#include "../PauseState/PauseState.h"
#include "../GameOverState/GameOverState.h"
#include "../../GameObject/Button/Button.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../Collisions/Collisions.h"
#include "../../ResultMessage/ResultMessage.h"

class PlayState : public GameState {
private:
    ResultMessage* message;
    Collisions* collisions;
    Map* map;
    GameWindow* gameWindow;
    ObjectManager* objectManager;
    static const std::string playID;
public:
    PlayState(GameWindow* gameWindow);
    ~PlayState();
    void update() override;
    void render() override;
    std::string getStateID() const override;
};

