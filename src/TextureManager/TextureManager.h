//
// Created by Евгений on 29.09.2022.
//

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <map>
#include <iostream>

class TextureManager {
private:
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textureMap;
public:
    TextureManager(SDL_Renderer* renderer);
    bool load(const char* pathToTexture,std::string textureID);
    void draw(std::string textureID, int x, int y, int width, int height, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string textureID, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clearFromTextureMap(std::string textureID);
    void getTextureSize(std::string textureID, int& width, int& height);
};
