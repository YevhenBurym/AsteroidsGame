//
// Created by Евгений on 22.07.2022.
//

#ifndef TEST_PAUSESTATE_H
#define TEST_PAUSESTATE_H

#include "GameState.h"
#include "../GameWindow/GameWindow.h"
#include "../InputComponent/InputComponent.h"
#include "../GameObject/Button.h"
#include "MenuState.h"

class PauseState : public GameState {
private:
    GameWindow* gameWindow;
    InputComponent* inputComponent;
    void s_pauseToMain();
    void s_resumePlay();

    static const std::string pauseID;
    std::vector<Button *> menuButtons;
public:
    PauseState(GameWindow* gameWindow, InputComponent* inputComponent);
    void update() override;
    void render() override;
    bool onEnter() override;
    bool onExit() override;
    std::string getStateID() const override;
};


#endif //TEST_PAUSESTATE_H
