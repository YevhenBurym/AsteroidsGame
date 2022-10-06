//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "../GameObject/Button/Button.h"
#include "../Map/Map.h"
#include "../ObjectManager/ObjectManager.h"
#include "../Collisions/Collisions.h"

class PlayState : public GameState {
private:
    static const std::string playID;
    std::vector<Button *> m_gameObjects;

    Collisions* collisions;
    Map* map;
    GameWindow* gameWindow;
    ObjectManager* objectManager;

public:
    PlayState(GameWindow* gameWindow);
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;
};

