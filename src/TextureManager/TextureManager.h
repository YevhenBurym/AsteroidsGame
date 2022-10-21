//
// Created by Евгений on 29.09.2022.
//

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <map>
#include <iostream>

class TextureManager {
private:
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Texture*> textureMap;
    std::map<std::string, TTF_Font*> fontMap;

public:
    explicit TextureManager(SDL_Renderer* renderer);
    void loadTexture(const char* pathToTexture, std::string textureID);
    void loadFont(const char* pathToFont, std::string fontID, int fontSize);
    void createTextureFromText(std::string fontID, std::string text, std::string textureID);
    void draw(std::string textureID, int x, int y, int width, int height, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string textureID, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clearFromTextureMap(std::string textureID);
    void clearFromFontMap(std::string fontID);
    void getTextureSize(std::string textureID, int& width, int& height);
    std::map<std::string, TTF_Font*>& getFontMap();
};
