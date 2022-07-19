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
    int hWindow, wWindow;
public:
    Window(const char* name, int width, int height, bool isFullscreen);
    ~Window();

    SDL_Renderer* getRenderer() const;
    void getSize(int& wScreen, int& hScreen);
    uint32_t getTickCounting();
    void showCursor(bool isShow);

    SDL_Texture* createTexture(const char* path);
    void drawTexture(SDL_Texture *texture, int x, int y);
    void drawTexture(SDL_Texture *texture, int x, int y, double angle);
    void destroyTexture(SDL_Texture *texture);
    void getTextureSize(SDL_Texture *texture, int &w, int &h);
};
