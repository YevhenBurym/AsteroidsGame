//
// Created by Евгений on 06.07.2022.
//

#pragma once

#include "GameManager.h"

class GameWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isCreate;
    bool isCursorShown;
    int hWindow, wWindow;
public:
    GameWindow(const char* name, int width, int height, bool isFullscreen);
    ~GameWindow();
    SDL_Renderer* getRenderer() const;
    bool getIsCreate() const;
    void getSize(int& wScreen, int& hScreen);
    uint32_t getTickCounting();
    void showCursor(bool isShow);
    bool getIsCursorShown() const;
};


