//
// Created by Евгений on 06.07.2022.
//

#include "GameWindow.h"
#include "../GameStates/MenuState/MenuState.h"

void GameWindow::loadSprites() {
    this->textureManager->loadTexture("assets\\back.png", "background");
    this->textureManager->loadTexture("assets\\border.png", "border");
    this->textureManager->loadTexture("assets\\ship.png", "spaceship");
    this->textureManager->loadTexture("assets\\small.png", "small_asteroid");
    this->textureManager->loadTexture("assets\\big.png", "big_asteroid");
    this->textureManager->loadTexture("assets\\reticle.png", "reticle");
    this->textureManager->loadTexture("assets\\bullet.png", "bullet");
    this->textureManager->loadTexture("assets\\startButton.png", "start_button");
    this->textureManager->loadTexture("assets\\exitButton.png", "exit_button");
    this->textureManager->loadTexture("assets\\resumeButton.png", "resume_button");
    this->textureManager->loadTexture("assets\\menuButton.png", "menu_button");
    this->textureManager->loadTexture("assets\\restartButton.png", "restart_button");
    this->textureManager->loadTexture("assets\\gameOver.png", "game_over");
    this->textureManager->loadTexture("assets\\shieldAbility.png", "shield_ability");
    this->textureManager->loadTexture("assets\\missileAbility.png", "missile_ability");
    this->textureManager->loadTexture("assets\\autoshootAbility.png", "autoshoot_ability");
    this->textureManager->loadTexture("assets\\shield.png", "shield");
    this->textureManager->loadTexture("assets\\missile.png", "missile");
    this->textureManager->loadFont("assets\\RAVIE.ttf", "ravie", 20);
    this->textureManager->createTextureFromText(this->textureManager->getFontMap()["ravie"],"DESTROYED ASTEROIDS: ", "result_title");
    this->textureManager->createTextureFromText(this->textureManager->getFontMap()["ravie"],"Big: ", "big_amount");
    this->textureManager->createTextureFromText(this->textureManager->getFontMap()["ravie"],"small: ", "small_amount");
}

GameWindow::GameWindow(GameParameters *parameters) {
    this->parameters = parameters;
    const char *gameName = "Asteroids";
    this->quitGame = false;
    this->window = nullptr;
    this->renderer = nullptr;
    this->size = {0,0};

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialize! SDL Error: %s" << SDL_GetError() << std::endl;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }

        Uint32 windowFlags = SDL_WINDOW_SHOWN;
        if (this->parameters->getIsFullScreen()) {
            windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP;
        }

        this->window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        this->parameters->getWScreen(), this->parameters->getHScreen(), windowFlags);
        if (this->window == nullptr) {
            std::cout << "Window could not be created! SDL Error: %s\n" << SDL_GetError();
        } else {
            SDL_GetWindowSize(this->window, &this->size.width, &this->size.height);
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
            if (this->renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL Error: %s\n" << SDL_GetError();
            } else {
                SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                }
                if( TTF_Init() == -1 ) {
                    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError() << std::endl;
                }
            }
        }

        this->inputHandler = new InputHandler();
        this->textureManager = new TextureManager(this->renderer);
        this->loadSprites();
        this->gameStateMachine = new StateMachine();
    }
}

GameWindow::~GameWindow() {
    delete this->parameters;
    delete this->inputHandler;
    delete this->textureManager;
    delete this->gameStateMachine;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
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

StateMachine *GameWindow::getGameStateMachine() const {
    return this->gameStateMachine;
}

InputHandler *GameWindow::getInputHadler() const {
    return this->inputHandler;
}

GameParameters *GameWindow::getParameters() const {
    return this->parameters;
}

void GameWindow::setFlagQuitGame(bool status) {
    this->quitGame = status;
}

bool GameWindow::getFlagQuitGame() const {
    return this->quitGame;
}