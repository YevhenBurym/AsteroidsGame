//
// Created by Евгений on 07.07.2022.
//

#pragma once

#include "GameWindow.h"

class Sprite {
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int wSprite, hSprite;
public:
    Sprite(const char* pathToTexture, GameWindow* window);
    ~Sprite();
    void draw(int x, int y);
    void draw(int x, int y, double angle);
    void getSize(int& w, int& h) const;
};
