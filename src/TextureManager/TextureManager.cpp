//
// Created by Евгений on 29.09.2022.
//

#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

bool TextureManager::load(const char* pathToTexture, std::string textureID)
{
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, pathToTexture);
    if (texture != nullptr ) {
        this->textureMap[textureID] = texture;
        return true;
    }
    std::cout << "Failed to load texture image!" << std::endl;
    return false;
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

void TextureManager::getTextureSize(std::string textureID, int &width, int &height) {
    SDL_QueryTexture(this->textureMap[textureID], nullptr, nullptr, &width, &height);
}