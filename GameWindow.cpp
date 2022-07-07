//
// Created by Евгений on 06.07.2022.
//

#include <iostream>
#include "GameWindow.h"

GameWindow::GameWindow(const char* name, int width, int height, bool isFullscreen) {
    this->window = nullptr;
    this->renderer = nullptr;
    this->isCreate = false;
    this->hWindow = 0;
    this->wWindow = 0;
    this->isCursorShown = true;

    //Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
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
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED/*| SDL_RENDERER_PRESENTVSYNC*/ );
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
                    this->isCreate = true;
                }
            }
        }
    }

}

GameWindow::~GameWindow() {
    SDL_DestroyRenderer( this->renderer );
    SDL_DestroyWindow( this->window );
    this->renderer = nullptr;
    this->window = nullptr;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *GameWindow::getRenderer() const {
    return this->renderer;
}

bool GameWindow::getIsCreate() const {
    return this->isCreate;
}

void GameWindow::getSize(int& wScreen, int& hScreen) {
    wScreen = this->wWindow;
    hScreen = this->hWindow;
}

uint32_t GameWindow::getTickCounting() {
    return SDL_GetTicks();
}

void GameWindow::showCursor(bool isShow) {
    this->isCursorShown = isShow;
}

bool GameWindow::getIsCursorShown() const {
    return this->isCursorShown;
}

void GameWindow::runGame(Game* game) {

        bool quit = false;
        //Event handler
        SDL_Event event;
        //Current time start time
        Uint32 startTime = 0;
//------------------------init--------------------------------------//
        game->init();
//------------------------------------------------------------------//
        //While application is running
        while( !quit ) {
            //Handle events on queue
            while( SDL_PollEvent( &event ) != 0 ) {
                //User requests quit
                if( event.type == SDL_QUIT ) {
                    quit = true;
                }
//--------------------MouseEvents-------------------------------------//
                if (event.type == SDL_MOUSEMOTION) {
                    game->onMouseMove(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                    event.motion.state = SDL_RELEASED;      // если не ставить, то при движении мыши ставит event.button.state == SDL_RELEASED
                }
                switch( event.button.button )
                {
                    case SDL_BUTTON_LEFT:
                        if (event.button.state == SDL_PRESSED) {
                            game->onMouseButtonClick(GameMouseButton::LEFT, false);
                        } else if (event.button.state == SDL_RELEASED) {
                            game->onMouseButtonClick(GameMouseButton::LEFT, true);
                        }
                        break;
                    case SDL_BUTTON_RIGHT:
                        if (event.button.state == SDL_PRESSED) {
                            game->onMouseButtonClick(GameMouseButton::RIGHT, false);
                        } else if (event.button.state == SDL_RELEASED) {
                            game->onMouseButtonClick(GameMouseButton::RIGHT, true);
                        }
                        break;
                    case SDL_BUTTON_MIDDLE:
                        if (event.button.state == SDL_PRESSED) {
                            game->onMouseButtonClick(GameMouseButton::MIDDLE, false);
                        } else if (event.button.state == SDL_RELEASED) {
                            game->onMouseButtonClick(GameMouseButton::MIDDLE, true);
                        }
                        break;
                }
//--------------------KeyEvents-------------------------------------//
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        if (event.key.state == SDL_PRESSED) {
                            game->onKeyPressed(GameKey::UP);
                        } else if (event.key.state == SDL_RELEASED) {
                            game->onKeyReleased(GameKey::UP);
                        }
                        break;
                    case SDLK_DOWN:
                        if (event.key.state == SDL_PRESSED) {
                            game->onKeyPressed(GameKey::DOWN);
                        } else if (event.key.state == SDL_RELEASED) {
                            game->onKeyReleased(GameKey::DOWN);
                        }
                        break;
                    case SDLK_LEFT:
                        if (event.key.state == SDL_PRESSED) {
                            game->onKeyPressed(GameKey::LEFT);
                        } else if (event.key.state == SDL_RELEASED) {
                            game->onKeyReleased(GameKey::LEFT);
                        }
                        break;
                    case SDLK_RIGHT:
                        if (event.key.state == SDL_PRESSED) {
                            game->onKeyPressed(GameKey::RIGHT);
                        } else if (event.key.state == SDL_RELEASED) {
                            game->onKeyReleased(GameKey::RIGHT);
                        }
                        break;
                }

            }

            //Clear screen
            SDL_RenderClear( this->renderer );
//----------------ShownCursor----------------------------------------//
            if ( this->isCursorShown ) {
                SDL_ShowCursor(SDL_ENABLE);
            } else {
                SDL_ShowCursor(SDL_DISABLE);
            }
//-------------------Tick-------------------------------------------//
            game->tick();
//------------------------------------------------------------------//
            SDL_RenderPresent( this->renderer );
            SDL_Delay(1);
        }

//-----------------Close--------------------------------------------//
        game->close();
//------------------------------------------------------------------//
        //Destroy window
        delete this;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
}



