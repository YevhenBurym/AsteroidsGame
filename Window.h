//
// Created by Евгений on 06.07.2022.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isCreate;
    bool isCursorShown;
    int hWindow, wWindow;
public:
    Window(const char* name, int width, int height, bool isFullscreen, bool isCursorShown);
    ~Window();
    SDL_Renderer* getRenderer() const;
    bool getIsCreate() const;
    void getSize(int& wScreen, int& hScreen);
    uint32_t getTickCounting();
    void updateWindow();
    SDL_Texture *createTexture(const char *path);
    void drawTexture(SDL_Texture *texture, int x, int y);
    void drawTexture(SDL_Texture *texture, int x, int y, double angle);
    void destroyTexture(SDL_Texture *texture);
    void getTextureSize(SDL_Texture *texture, int &w, int &h);
};
