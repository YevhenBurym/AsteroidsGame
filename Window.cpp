//
// Created by Евгений on 06.07.2022.
//

#include <iostream>
#include "Window.h"

Window::Window(const char* name, int width, int height, bool isFullscreen) {
    this->window = nullptr;
    this->renderer = nullptr;
    this->hWindow = 0;
    this->wWindow = 0;

    //Initialize SDL
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
        std::cout << "SDL could not initialize! SDL Error: %s" << SDL_GetError() << std::endl;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        Uint32 windowFlags = SDL_WINDOW_SHOWN;
        if (isFullscreen) {
            windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        this->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                        windowFlags);
        if( this->window == nullptr ) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
        } else {
            //windowSize
            SDL_GetWindowSize(this->window, &this->wWindow, &this->hWindow);
            //Create vsynced renderer for window
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED );
            if (this->renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                } else {
                }
            }
        }
    }

}

Window::~Window() {
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    this->renderer = nullptr;
    this->window = nullptr;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *Window::getRenderer() const {
    return this->renderer;
}

void Window::getSize(int& wScreen, int& hScreen) {
    wScreen = this->wWindow;
    hScreen = this->hWindow;
}

uint32_t Window::getTickCounting() {
    return SDL_GetTicks();
}

SDL_Texture* Window::createTexture(const char* path) {
    SDL_Texture* newTexture = nullptr;

    newTexture = IMG_LoadTexture(this->renderer, path);

    if( newTexture == nullptr ) {
        std::cout << "Failed to load texture image!" << std::endl;
    }
    return newTexture;
}

void Window::drawTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect drawParams{x, y,0,0};
    this->getTextureSize(texture,drawParams.w,drawParams.h);

    SDL_RenderCopy( this->renderer, texture, nullptr, &drawParams );
}

void Window::drawTexture(SDL_Texture* texture, int x, int y, double angle) {
    SDL_Rect drawParams{x, y,0,0};
    this->getTextureSize(texture,drawParams.w,drawParams.h);

    SDL_RenderCopyEx( this->renderer, texture, nullptr, &drawParams, angle, nullptr, SDL_FLIP_NONE );
}

void Window::destroyTexture(SDL_Texture* texture) {
    //Free loaded image
    SDL_DestroyTexture( texture );
    texture = nullptr;
}

void Window::getTextureSize(SDL_Texture* texture, int& w, int& h) {
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}

void Window::showCursor(bool isShow) {
    if ( isShow ) {
        SDL_ShowCursor(SDL_ENABLE);
    } else {
        SDL_ShowCursor(SDL_DISABLE);
    }
}


