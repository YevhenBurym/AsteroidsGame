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

struct WindowSize {
    int width;
    int height;
};

class GameWindow {
private:
    InputComponent* inputHandler;
    TextureManager* textureManager;
    GameStateMachine* gameStateMachine;
    SDL_Window* window;
    SDL_Renderer* renderer;
    WindowSize size;
    bool quitGame;
    void loadSprites();
public:
    GameWindow(const char* name, int width, int height, bool isFullscreen);
    ~GameWindow();

    SDL_Renderer* getRenderer() const;
    TextureManager* getTextureManager() const;
    WindowSize getSize() const;
    GameStateMachine* getGameStateMachine() const;
    InputComponent* getInputHadler() const;
    bool getFlagQuitGame() const;
    void setFlagQuitGame(bool status);
};
