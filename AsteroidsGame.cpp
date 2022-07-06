//
// Created by Евгений on 04.07.2022.
//

#include "AsteroidsGame.h"

void AsteroidsGame::createSprites() {
    this->sprites.backgroundSprite = createTexture("data\\background.png");
    this->sprites.dotSprite = createTexture("data\\dot.png");
}

void AsteroidsGame::drawBackground() {
    int hSprite, wSprite;
    int rowLim = this->hScreen;
    int colLim = this->wScreen;
    getTextureSize(this->sprites.backgroundSprite, wSprite, hSprite);

    if (this->hScreen % hSprite != 0) {
        rowLim += hSprite;
    }
    if (this->wScreen % wSprite != 0) {
        colLim += wSprite;
    }
    for ( int row = 0; row <= rowLim; row += hSprite ) {
        for ( int col = 0; col <= colLim; col += wSprite ) {
            drawTexture(this->sprites.backgroundSprite, col, row);
        }
    }
}

void AsteroidsGame::drawMapBorder() {
    int hSprite, wSprite;
    getTextureSize(this->sprites.dotSprite, wSprite, hSprite);

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
        drawTexture(this->sprites.dotSprite, i, minYCoord);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        drawTexture(this->sprites.dotSprite, minXCoord, i);
    }
    for (int i = minXCoord; i <= maxXCoord; i += wSprite) {
        drawTexture(this->sprites.dotSprite, i, maxYCoord);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        drawTexture(this->sprites.dotSprite, maxXCoord, i);
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
}

void AsteroidsGame::preInit(int &width, int &height, bool &fullscreen) {
    width = this->wScreen;
    height = this->hScreen;
    fullscreen = false;
}

bool AsteroidsGame::init() {
    showMouseCursor(false);
    this->createSprites();
    this->map = new Map(this->wMap, this->hMap, this->hScreen, this->wScreen);
    this->unitManager = new UnitManager(this->asteroidsLimit, this->ammoLimit, 200, this);
    this->unitManager->createAvatar();
    return true;
}

void AsteroidsGame::close() {
    delete this->map;
    delete this->unitManager;
    destroyTexture(this->sprites.backgroundSprite);
    destroyTexture(this->sprites.dotSprite);
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

void AsteroidsGame::onMouseMove(int x, int y, int xrelative, int yrelative) {
    this->unitManager->setXReticle(x);
    this->unitManager->setYReticle(y);
}

void AsteroidsGame::onMouseButtonClick(GameMouseButton button, bool isReleased) {
    if (button == GameMouseButton::LEFT && isReleased) {
        this->unitManager->makeShoot();
    }
}

void AsteroidsGame::onKeyPressed(GameKey k) {
    int V = 300;

    if (k == GameKey::UP) {
        this->map->setV(V, 270);
    }
    if (k == GameKey::DOWN) {
        this->map->setV(V, 90);
    }
    if (k == GameKey::LEFT) {
        this->map->setV(V, 0);
    }
    if (k == GameKey::RIGHT) {
        this->map->setV(V, 180);
    }
}

void AsteroidsGame::onKeyReleased(GameKey k) {
    if (k == GameKey::RIGHT || k == GameKey::LEFT || k == GameKey::UP || k == GameKey::DOWN) {
        this->unitManager->setIsNeededDeacc(true);
    }
}

const char *AsteroidsGame::getTitle() {
    return "asteroids";
}

void AsteroidsGame::restart() {
    this->close();
    this->init();
}

Map* AsteroidsGame::getMap() const {
    return this->map;
}