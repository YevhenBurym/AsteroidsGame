//
// Created by Евгений on 29.09.2022.
//

#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void TextureManager::loadTexture(const char* pathToTexture, std::string textureID)
{
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, pathToTexture);
    if (texture != nullptr ) {
        this->textureMap[textureID] = texture;
        return;
    }
    std::cout << "Failed to load texture image!" << std::endl;
}

void TextureManager::loadFont(const char* pathToFont, std::string fontID, int fontSize) {
    TTF_Font* font = TTF_OpenFont(pathToFont, fontSize);
    if (font != nullptr) {
        this->fontMap[fontID] = font;
        return;
    }
    std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
}

void TextureManager::draw(std::string textureID, int x, int y, int width, int height, double angle, SDL_RendererFlip flip) {
    SDL_Rect srcRect{0,0, width, height};
    SDL_Rect destRect{x, y, width, height};
    SDL_RenderCopyEx(this->renderer, this->textureMap[textureID], &srcRect, &destRect, angle, nullptr, flip);
}

void TextureManager::drawFrame(std::string textureID, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip) {
    SDL_Rect srcRect{width * currentFrame,
                     height * (currentRow - 1),
                     width,
                     height};
    SDL_Rect destRect{x, y, width, height};
    SDL_RenderCopyEx(this->renderer, this->textureMap[textureID], &srcRect, &destRect, 0, nullptr, flip);
}

void TextureManager::clearFromTextureMap(std::string textureID) {
    this->textureMap.erase(textureID);
}

void TextureManager::clearFromFontMap(std::string fontID) {
    this->fontMap.erase(fontID);
}

void TextureManager::getTextureSize(std::string textureID, int &width, int &height) {
    SDL_QueryTexture(this->textureMap[textureID], nullptr, nullptr, &width, &height);
}

void TextureManager::createTextureFromText(std::string fontID, std::string text, std::string textureID) {
    SDL_Color textColor = {0xFF, 0xFF, 0xFF};
    SDL_Surface* textSurface = TTF_RenderText_Solid(this->fontMap[fontID], text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    } else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if( texture != nullptr ) {
            this->textureMap[textureID] = texture;
        } else {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(textSurface);
    }
}

std::map<std::string, TTF_Font*>& TextureManager::getFontMap() {
    return this->fontMap;
}
