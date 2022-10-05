//
// Created by Евгений on 06.07.2022.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "../TextureManager/TextureManager.h"
#include "../GameStates/GameStateMachine.h"
#include "../InputComponent/InputComponent.h"
#include "../GameParameters/GameParameters.h"

struct WindowSize {
    int width;
    int height;
};

class GameWindow {
private:
    GameParameters* parameters;
    InputComponent* inputHandler;
    TextureManager* textureManager;
    GameStateMachine* gameStateMachine;
    SDL_Window* window;
    SDL_Renderer* renderer;
    WindowSize size;
    bool quitGame;
    void loadSprites();
public:
    GameWindow(GameParameters* parameters);
    ~GameWindow();

    SDL_Renderer* getRenderer() const;
    TextureManager* getTextureManager() const;
    WindowSize getSize() const;
    GameStateMachine* getGameStateMachine() const;
    InputComponent* getInputHadler() const;
    GameParameters* getParameters() const;
    bool getFlagQuitGame() const;
    void setFlagQuitGame(bool status);
};
