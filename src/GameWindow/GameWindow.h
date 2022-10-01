//
// Created by Евгений on 06.07.2022.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "../SpriteManager/SpriteManager.h"

struct WindowSize {
    int width;
    int height;
};

class GameWindow {
private:
    SpriteManager* spriteManager;
    SDL_Window* window;
    SDL_Renderer* renderer;
    WindowSize size;
    void loadSprites();
public:
    GameWindow(const char* name, int width, int height, bool isFullscreen);
    ~GameWindow();

    SDL_Renderer* getRenderer() const;
    SpriteManager* getSpriteManager() const;
    WindowSize getSize() const;
};
