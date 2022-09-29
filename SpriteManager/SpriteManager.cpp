//
// Created by Евгений on 29.09.2022.
//

#include "SpriteManager.h"

SpriteManager::SpriteManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

bool SpriteManager::load(const char* pathToTexture, std::string textureID)
{
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, pathToTexture);
    if (texture != nullptr ) {
        this->textureMap[textureID] = texture;
        return true;
    }
    std::cout << "Failed to load texture image!" << std::endl;
    return false;
}

void SpriteManager::draw(std::string textureID, int x, int y, int width, int height, double angle, SDL_RendererFlip flip) {
    SDL_Rect srcRect{0,0, width, height};
    SDL_Rect destRect{x, y, width, height};
    SDL_RenderCopyEx(this->renderer, this->textureMap[textureID], &srcRect, &destRect, angle, nullptr, flip);
}

void SpriteManager::drawFrame(std::string textureID, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_RendererFlip flip) {
    SDL_Rect srcRect{width * currentFrame,
                     height * (currentRow - 1),
                     width,
                     height};
    SDL_Rect destRect{x, y, width, height};
    SDL_RenderCopyEx(this->renderer, this->textureMap[textureID], &srcRect, &destRect, 0, nullptr, flip);
}

void SpriteManager::clearFromTextureMap(std::string textureID) {
    this->textureMap.erase(textureID);
}

void SpriteManager::getTextureSize(std::string textureID, int &width, int &height) {
    SDL_QueryTexture(this->textureMap[textureID], nullptr, nullptr, &width, &height);
}