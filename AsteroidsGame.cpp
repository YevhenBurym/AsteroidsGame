//
// Created by Евгений on 04.07.2022.
//

#include "AsteroidsGame.h"

void AsteroidsGame::createSprites() {
    this->sprites.backgroundSprite = new Sprite("data\\background.png",this->gameWindow);
    this->sprites.dotSprite = new Sprite("data\\dot.png",this->gameWindow);
}

void AsteroidsGame::drawBackground() {
    int hSprite, wSprite;
    int rowLim = this->hScreen;
    int colLim = this->wScreen;

    this->sprites.backgroundSprite->getSize(wSprite,hSprite);

    if (this->hScreen % hSprite != 0) {
        rowLim += hSprite;
    }
    if (this->wScreen % wSprite != 0) {
        colLim += wSprite;
    }
    for ( int row = 0; row <= rowLim; row += hSprite ) {
        for ( int col = 0; col <= colLim; col += wSprite ) {
            this->sprites.backgroundSprite->draw(col,row);
        }
    }
}

void AsteroidsGame::drawMapBorder() {
    int hSprite, wSprite;
    this->sprites.dotSprite->getSize(wSprite,hSprite);

    int minXCoord = 0 - this->map->getMapOffsetCoord().x + this->map->getX();
    int maxXCoord = this->map->getWMap() - this->map->getMapOffsetCoord().x + this->map->getX();
    int minYCoord = 0 - this->map->getMapOffsetCoord().y + this->map->getY();
    int maxYCoord = this->map->getHMap() - this->map->getMapOffsetCoord().y + this->map->getY();

    if (maxYCoord % hSprite != 0) {
        maxYCoord += hSprite;
    }
    if (maxXCoord % wSprite != 0) {
        maxXCoord += wSprite;
    }

    for (int i = minXCoord; i <= maxXCoord; i += wSprite) {
        this->sprites.dotSprite->draw(i,minYCoord);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        this->sprites.dotSprite->draw(minXCoord,i);
    }
    for (int i = minXCoord; i <= maxXCoord; i += wSprite) {
        this->sprites.dotSprite->draw(i,maxYCoord);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        this->sprites.dotSprite->draw(maxXCoord,i);
    }
}

AsteroidsGame::AsteroidsGame(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability) {
    if (wMap < wScreen) {
        wMap = wScreen;
    }
    if (hMap < hScreen) {
        hMap = wScreen;
    }
    this->hMap = hMap;
    this->wMap = wMap;
    this->wScreen = wScreen;
    this->hScreen = hScreen;
    this->asteroidsLimit = asteroidsLimit;
    this->ammoLimit = ammoLimit;

    this->gameWindow = new GameWindow("Asteroids",this->wScreen, this->hScreen, false);
}

bool AsteroidsGame::init() {
    this->gameWindow->showCursor(false);
    this->createSprites();
    this->map = new Map(this->wMap, this->hMap, this->hScreen, this->wScreen);
    this->unitManager = new UnitManager(this->asteroidsLimit, this->ammoLimit, 200, this);
    this->unitManager->createAvatar();
    return true;
}

void AsteroidsGame::close() {
    delete this->map;
    delete this->unitManager;
    delete this->sprites.backgroundSprite;
    delete this->sprites.dotSprite;
}

bool AsteroidsGame::tick() {
    this->drawBackground();
    this->drawMapBorder();
    this->unitManager->createAsteroids();
    this->unitManager->checkCollisions();
    this->unitManager->drawReticle();
    this->unitManager->deAcceleration();
    this->unitManager->calcOffset();
    this->unitManager->shipHeadAngle();

    return false;
}

void AsteroidsGame::restart() {
    this->close();
    this->init();
}

Map* AsteroidsGame::getMap() const {
    return this->map;
}

GameWindow *AsteroidsGame::getWindow() const {
    return this->gameWindow;
}

void AsteroidsGame::runGame() {

    bool quit = false;
    //Event handler
    SDL_Event event;
    this->inputHandler = new InputHandler(this);
    //Current time start time
    Uint32 startTime = 0;
//------------------------init--------------------------------------//
    this->init();
//------------------------------------------------------------------//
    //While application is running
    while( !quit ) {
        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ) {
            //User requests quit
            if( event.type == SDL_QUIT ) {
                quit = true;
            }
            this->inputHandler->handleInput(event);
        }

        //Clear screen
        SDL_RenderClear( this->gameWindow->getRenderer() );
//----------------ShownCursor----------------------------------------//
        if ( this->gameWindow->getIsCursorShown() ) {
            SDL_ShowCursor(SDL_ENABLE);
        } else {
            SDL_ShowCursor(SDL_DISABLE);
        }
//-------------------Tick-------------------------------------------//
        this->tick();
//------------------------------------------------------------------//
        SDL_RenderPresent( this->gameWindow->getRenderer() );
        SDL_Delay(1);
    }

//-----------------Close--------------------------------------------//
    this->close();
//------------------------------------------------------------------//
    //Destroy window
    delete this->inputHandler;
    delete this->gameWindow;
}

UnitManager* AsteroidsGame::getUnitManager() const {
    return this->unitManager;
}
