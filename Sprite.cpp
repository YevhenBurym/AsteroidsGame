//
// Created by Евгений on 07.07.2022.
//

#include "Sprite.h"

Sprite::Sprite(const char* pathToTexture, Window* window) {
    this->renderer = window->getRenderer();
    this->texture = nullptr;

    this->texture = IMG_LoadTexture(this->renderer, pathToTexture);

    if( this->texture == nullptr ) {
        std::cout << "Failed to load texture image!" << std::endl;
    }
    SDL_QueryTexture(this->texture, nullptr, nullptr, &this->wSprite, &this->hSprite);
}

Sprite::~Sprite() {
    SDL_DestroyTexture( this->texture );
    this->texture = nullptr;
}

void Sprite::draw(int x, int y) {
    SDL_Rect drawParams{x, y,this->wSprite,this->hSprite};

    SDL_RenderCopy( this->renderer, texture, nullptr, &drawParams );
}

void Sprite::draw(int x, int y, double angle) {
    SDL_Rect drawParams{x, y,this->wSprite,this->hSprite};
    SDL_RenderCopyEx(this->renderer, texture, nullptr, &drawParams, angle,nullptr,SDL_FLIP_NONE);
}

void Sprite::getSize(int &w, int &h) const {
    w = this->wSprite;
    h = this->hSprite;
}