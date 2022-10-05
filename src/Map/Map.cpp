#include "Map.h"

Map::Map(GameWindow* window) {
	this->window = window;
    this->hMap = window->getParameters()->getHMap();
    this->wMap = window->getParameters()->getWMap();
    this->Vx = 0;
    this->Vy = 0;
    this->isNeedDeAcc = false;
    this->mapInit();
}

void Map::calcCoord(double Vx, double Vy, double step) {
    this->xyRelative.setX(this->xyRelative.getX() + Vx * step);
    this->xyRelative.setY(this->xyRelative.getY() + Vy * step);
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

double Map::getX() const {
	return this->xyRelative.getX();
}

double Map::getY() const {
	return this->xyRelative.getY();
}

double Map::getVx() const {
	return this->Vx;
}

double Map::getVy() const {
	return this->Vy;
}

void Map::setX(double x) {
	this->xyRelative.setX(x);
}
void Map::setY(double y) {
	this->xyRelative.setY(y);
}

void Map::setVx(double vx) {
    this->Vx = vx;
}

void Map::setVy(double vy) {
    this->Vy = vy;
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

    int minXCoord = 0 - this->getMapOffsetCoord().getX() + this->getX();
    int maxXCoord = this->getWMap() - this->getMapOffsetCoord().getX() + this->getX();
    int minYCoord = 0 - this->getMapOffsetCoord().getY() + this->getY();
    int maxYCoord = this->getHMap() - this->getMapOffsetCoord().getY() + this->getY();

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
    this->Vx = 0;
    this->Vy = 0;
}

void Map::update() {
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_UP)) {
        this->Vy = 1;
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_DOWN)) {
        this->Vy = -1;
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_LEFT)) {
        this->Vx = 1;
    } else {
        this->isNeedDeAcc = true;
    }
    if (this->window->getInputHadler()->isKeyDown(SDL_SCANCODE_RIGHT)) {
        this->Vx = -1;
    } else {
        this->isNeedDeAcc = true;
    }

    float acc = 0.003;
    float accuracy = 0.001;

    if (this->isNeedDeAcc) {
        if (this->Vx > 0) {
            this->Vx -= acc;
        } else if (this->Vx < 0) {
            this->Vx += acc;
        }

        if (this->Vy > 0) {
            this->Vy -= acc;
        } else if (this->Vy < 0) {
            this->Vy += acc;
        }

        if ( std::abs(this->Vx) <= accuracy && std::abs(this->Vy) <= accuracy ) {
            this->Vx = 0;
            this->Vy = 0;
            this->isNeedDeAcc = false;
        }
    }
}

void Map::setIsNeededDeAcc(bool state) {
    this->isNeedDeAcc = true;
}