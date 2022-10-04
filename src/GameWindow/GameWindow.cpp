//
// Created by Евгений on 06.07.2022.
//

#include "GameWindow.h"
#include "../GameStates/MenuState.h"

void GameWindow::loadSprites() {
    this->textureManager->load("assets\\back.png", "background");
    this->textureManager->load("assets\\border.png", "border");
    this->textureManager->load("assets\\ship.png", "spaceship");
    this->textureManager->load("assets\\small.png", "small_asteroid");
    this->textureManager->load("assets\\big.png", "big_asteroid");
    this->textureManager->load("assets\\reticle.png", "reticle");
    this->textureManager->load("assets\\bullet.png", "bullet");
    this->textureManager->load("assets\\startButton.png", "start_button");
    this->textureManager->load("assets\\exitButton.png", "exit_button");
    this->textureManager->load("assets\\resumeButton.png", "resume_button");
    this->textureManager->load("assets\\menuButton.png", "menu_button");
    this->textureManager->load("assets\\restartButton.png", "restart_button");
    this->textureManager->load("assets\\gameOver.png", "game_over");
}

GameWindow::GameWindow(const char *name, int width, int height, bool isFullscreen) {
    this->quitGame = false;
    this->window = nullptr;
    this->renderer = nullptr;
    this->size.width = 0;
    this->size.height = 0;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
        if (this->window == nullptr) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
        } else {
            //windowSize
            SDL_GetWindowSize(this->window, &this->size.width, &this->size.height);
            //Create vsynced renderer for window
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
            if (this->renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
            } else {
                //Initialize renderer color
                //SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_SetRenderDrawColor(this->renderer,0,0,0,255);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
                } else {
                }
            }
        }
        this->inputHandler = new InputComponent();
        this->textureManager = new TextureManager(this->renderer);
        this->loadSprites();
        this->gameStateMachine = new GameStateMachine();
    }
}

GameWindow::~GameWindow() {
    delete this->inputHandler;
    delete this->textureManager;
    delete this->gameStateMachine;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->renderer = nullptr;
    this->window = nullptr;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *GameWindow::getRenderer() const {
    return this->renderer;
}

TextureManager *GameWindow::getTextureManager() const {
    return this->textureManager;
}

WindowSize GameWindow::getSize() const {
    return this->size;
}

GameStateMachine *GameWindow::getGameStateMachine() const {
    return this->gameStateMachine;
}

InputComponent* GameWindow::getInputHadler() const {
    return this->inputHandler;
}

void GameWindow::setFlagQuitGame(bool status) {
    this->quitGame = status;
}

bool GameWindow::getFlagQuitGame() const {
    return this->quitGame;
}