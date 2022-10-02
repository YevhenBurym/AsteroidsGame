//
// Created by Евгений on 06.07.2022.
//

#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "../TextureManager/TextureManager.h"

struct WindowSize {
    int width;
    int height;
};

class GameWindow {
private:
    TextureManager* spriteManager;
    SDL_Window* window;
    SDL_Renderer* renderer;
    WindowSize size;
    void loadSprites();
public:
    GameWindow(const char* name, int width, int height, bool isFullscreen);
    ~GameWindow();

    SDL_Renderer* getRenderer() const;
    TextureManager* getSpriteManager() const;
    WindowSize getSize() const;
};
