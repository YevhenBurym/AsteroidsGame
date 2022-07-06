//
// Created by Евгений on 03.07.2022.
//

#include "GameManager.h"

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static bool isCursorShown = true;

SDL_Texture* createTexture(const char* path) {
    SDL_Texture* newTexture = nullptr;

    newTexture = IMG_LoadTexture(renderer, path);

    if( newTexture == nullptr ) {
        std::cout << "Failed to load texture image!" << std::endl;
    }
    return newTexture;
}

void drawTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect drawParams{x, y,0,0};
    getTextureSize(texture,drawParams.w,drawParams.h);

    SDL_RenderCopy( renderer, texture, nullptr, &drawParams );
}

void drawTexture(SDL_Texture* texture, int x, int y, double angle) {
    SDL_Rect drawParams{x, y,0,0};
    getTextureSize(texture,drawParams.w,drawParams.h);

    SDL_RenderCopyEx(renderer, texture, nullptr, &drawParams, angle,nullptr,SDL_FLIP_NONE);
}

void destroyTexture(SDL_Texture* texture) {
    //Free loaded image
    SDL_DestroyTexture( texture );
    texture = nullptr;
}

void getTextureSize(SDL_Texture* texture, int& w, int& h) {
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
}

void getWindowSize(int& wScreen, int& hScreen) {
    SDL_GetWindowSize(window, &wScreen, &hScreen);
}

uint32_t getTickCounting() {
    return SDL_GetTicks();
}

void showMouseCursor(bool isShow) {
    isCursorShown = isShow;
}

void runGame(Game* game) {
    //Initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        //success = false;
    } else {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //---------------Create window----------------//
        Uint32 windowFlags = SDL_WINDOW_SHOWN;
        int w, h;
        bool isFullScreen;
        game->preInit(w,h,isFullScreen);
        if (isFullScreen) {
            windowFlags = windowFlags|SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        window = SDL_CreateWindow( game->getTitle(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, windowFlags );
        //----------------------------------------------//
        if( window == nullptr ) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
            //success = false;
        } else {
            //Create vsynced renderer for window
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED/*| SDL_RENDERER_PRESENTVSYNC*/ );
            if( renderer == nullptr ) {
                std::cout <<  "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
                //success = false;
            } else {
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                    //success = false;
                } else {
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
                        SDL_RenderClear( renderer );
//----------------ShownCursor----------------------------------------//
                        if (isCursorShown) {
                            SDL_ShowCursor(SDL_ENABLE);
                        } else {
                            SDL_ShowCursor(SDL_DISABLE);
                        }
//-------------------Tick-------------------------------------------//
                        game->tick();
//------------------------------------------------------------------//
                        SDL_RenderPresent( renderer );
                        SDL_Delay(1);
                    }

//-----------------Close--------------------------------------------//
                    game->close();
//------------------------------------------------------------------//
                    //Destroy window
                    SDL_DestroyRenderer( renderer );
                    SDL_DestroyWindow( window );
                    window = nullptr;
                    renderer = nullptr;

                    //Quit SDL subsystems
                    IMG_Quit();
                    SDL_Quit();
                }
            }
        }
    }
}


