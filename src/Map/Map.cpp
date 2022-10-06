#include "Map.h"

Map::Map(GameWindow* window) {
	this->window = window;
    this->hMap = window->getParameters()->getHMap();
    this->wMap = window->getParameters()->getWMap();
    this->Vxy = {0,0};
    this->isNeedDeAcc = false;
    //this->mapInit();

    this->offset.setX(this->wMap / 2 - this->window->getSize().width / 2);
    this->offset.setY(this->hMap / 2 - this->window->getSize().height / 2);
    this->xyRelative = {0,0};
}

void Map::calcCoord() {
    this->xyRelative.setX(this->xyRelative.getX() + this->Vxy.getX() * 2);
    this->xyRelative.setY(this->xyRelative.getY() + this->Vxy.getY() * 2);
}

int Map::getHMap() const {
	return this->hMap;
}

int Map::getWMap() const {
	return this->wMap;
}

Vector2D Map::getMapOffsetCoord() const {
	return this->offset;
}

Vector2D Map::getXY() const {
    return this->xyRelative;
}

Vector2D Map::getVxy() const {
    return this->Vxy;
}

void Map::setX(double x) {
	this->xyRelative.setX(x);
}
void Map::setY(double y) {
	this->xyRelative.setY(y);
}

void Map::drawBackground() {
    int hSprite, wSprite;
    int wScreen = this->window->getSize().width;
    int hScreen = this->window->getSize().height;
    int rowLim = hScreen;
    int colLim = wScreen;

    this->window->getTextureManager()->getTextureSize("background", wSprite, hSprite);
    if (hScreen % hSprite != 0) {
        rowLim += hSprite;
    }
    if (wScreen % wSprite != 0) {
        colLim += wSprite;
    }
    for ( int row = 0; row <= rowLim; row += hSprite ) {
        for ( int col = 0; col <= colLim; col += wSprite ) {
            this->window->getTextureManager()->draw("background", col, row, wSprite, hSprite);
        }
    }
}

void Map::drawBorder() {
    int hSprite, wSprite;
    this->window->getTextureManager()->getTextureSize("border", wSprite, hSprite);

    int minXCoord = 0 - this->getMapOffsetCoord().getX() + this->xyRelative.getX();
    int maxXCoord = this->getWMap() - this->getMapOffsetCoord().getX() + this->xyRelative.getX();
    int minYCoord = 0 - this->getMapOffsetCoord().getY() + this->xyRelative.getY();
    int maxYCoord = this->getHMap() - this->getMapOffsetCoord().getY() + this->xyRelative.getY();

    if (maxYCoord % hSprite != 0) {
        maxYCoord += hSprite;
    }
    if (maxXCoord % wSprite != 0) {
        maxXCoord += wSprite;
    }

    for (int i = minXCoord; i <= maxXCoord; i += wSprite) {
        this->window->getTextureManager()->draw("border", i, minYCoord, wSprite, hSprite);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        this->window->getTextureManager()->draw("border", minXCoord, i, wSprite, hSprite);
    }
    for (int i = minXCoord; i <= maxXCoord; i += wSprite) {
        this->window->getTextureManager()->draw("border", i, maxYCoord, wSprite, hSprite);
    }
    for (int i = minYCoord; i <= maxYCoord; i += hSprite) {
        this->window->getTextureManager()->draw("border", maxXCoord, i, wSprite, hSprite);
    }
}

void Map::render() {
    this->drawBackground();
    this->drawBorder();
}

void Map::mapInit() {
    this->isNeedDeAcc = false;
    int wScreen = this->window->getSize().width;
    int hScreen = this->window->getSize().height;
    this->offset.setX(this->wMap / 2 - wScreen / 2);
    this->offset.setY(this->hMap / 2 - hScreen / 2);
    this->xyRelative = {0,0};
    this->Vxy = {0,0};
}

void Map::update() {
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_UP)) {
        this->Vxy.setY(1);
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_DOWN)) {
        this->Vxy.setY(-1);
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_LEFT)) {
        this->Vxy.setX(1);
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        this->Vxy.setX(-1);
    } else {
        this->isNeedDeAcc = true;
    }

    float acc = 0.003;
    float accuracy = 0.001;

    if (this->isNeedDeAcc) {
        if (this->Vxy.getX() > 0) {
            this->Vxy.setX(Vxy.getX() - acc);
        } else if (this->Vxy.getX() < 0) {
            this->Vxy.setX(Vxy.getX() + acc);
        }

        if (this->Vxy.getY() > 0) {
            this->Vxy.setY(Vxy.getY() - acc);
        } else if (this->Vxy.getY() < 0) {
            this->Vxy.setY(Vxy.getY() + acc);
        }

        if ( std::abs(this->Vxy.getX()) <= accuracy && std::abs(this->Vxy.getY()) <= accuracy ) {
            this->Vxy = {0 ,0};
            this->isNeedDeAcc = false;
        }
    }
    this->calcCoord();
}