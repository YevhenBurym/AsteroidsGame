//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "Window.h"

class Sprite {
private:
    Window* window;
    SDL_Texture* texture;
    int wSprite, hSprite;
public:
    Sprite(const char* pathToTexture, Window* window);
    ~Sprite();
    void draw(int x, int y);
    void draw(int x, int y, double angle);
    void getSize(int& w, int& h) const;
};
