//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include <vector>
#include "../PlayState/PlayState.h"
#include "../../GameObject/Button/Button.h"
#include "../../GameWindow/GameWindow.h"

class MenuState : public GameState {
private:
    GameWindow* gameWindow;
    std::vector<Button*> menuButtons;
    static const std::string menuID;
public:
    MenuState(GameWindow* gameWindow);
    ~MenuState() override;
    void update() override;
    void render() override;
    std::string getStateID() const override;

};
