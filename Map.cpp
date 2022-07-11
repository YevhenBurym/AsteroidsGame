#include "Map.h"

Map::Map(int wMap, int hMap, Window* window) {
	this->hMap = hMap;
	this->wMap = wMap;
    int wScreen, hScreen;
    window->getSize(wScreen,hScreen);
	this->offset.x = wMap / 2 - wScreen / 2;
	this->offset.y = hMap / 2 - hScreen / 2;
	this->xyRelative.x = 0;
	this->xyRelative.y = 0;
	this->V.v = 0;
	this->V.theta = 0;
	this->Vx = 0;
	this->Vy = 0;
	this->window = window;
    this->createMapSprites();
    this->createSprites();
}

Map::~Map() {
    delete this->sprites.backgroundSprite;
    delete this->sprites.dotSprite;
    this->destroySprites();
}


void Map::calcCoord(double Vx, double Vy, double step) {
	this->xyRelative.x += Vx * step;
	this->xyRelative.y += Vy * step;
}

int Map::getHMap() const {
	return this->hMap;
}

int Map::getWMap() const {
	return this->wMap;
}

CoordXY Map::getMapOffsetCoord() const {
	return this->offset;
}

double Map::getX() const {
	return this->xyRelative.x;
}

double Map::getY() const {
	return this->xyRelative.y;
}

double Map::getVx() const {
	return this->Vx;
}

double Map::getVy() const {
	return this->Vy;
}

Velocity Map::getV() const {
	return this->V;
}

void Map::setX(double x) {
	this->xyRelative.x = x;
}
void Map::setY(double y) {
	this->xyRelative.y = y;
}

void Map::setV(double v, double theta) {
	this->V.v = v;
	this->V.theta = theta;
	this->Vx = v * cos(this->V.theta * 3.14/180);
	this->Vy = -v * sin(this->V.theta * 3.14/180);
}

void Map::setVx(double vx) {
    this->Vx = vx;
}

void Map::setVy(double vy) {
    this->Vy = vy;
}

void Map::createMapSprites() {
    this->sprites.backgroundSprite = new Sprite("data\\background.png",this->window);
    this->sprites.dotSprite = new Sprite("data\\dot.png",this->window);
}

void Map::drawBackground() {
    int hSprite, wSprite;
    int wScreen, hScreen;
    this->window->getSize(wScreen,hScreen);
    int rowLim = hScreen;
    int colLim = wScreen;

    this->sprites.backgroundSprite->getSize(wSprite,hSprite);

    if (hScreen % hSprite != 0) {
        rowLim += hSprite;
    }
    if (wScreen % wSprite != 0) {
        colLim += wSprite;
    }
    for ( int row = 0; row <= rowLim; row += hSprite ) {
        for ( int col = 0; col <= colLim; col += wSprite ) {
            this->sprites.backgroundSprite->draw(col,row);
        }
    }
}

void Map::drawBorder() {
    int hSprite, wSprite;
    this->sprites.dotSprite->getSize(wSprite,hSprite);

    int minXCoord = 0 - this->getMapOffsetCoord().x + this->getX();
    int maxXCoord = this->getWMap() - this->getMapOffsetCoord().x + this->getX();
    int minYCoord = 0 - this->getMapOffsetCoord().y + this->getY();
    int maxYCoord = this->getHMap() - this->getMapOffsetCoord().y + this->getY();

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

void Map::draw() {
    this->drawBackground();
    this->drawBorder();
}

void Map::createSprites() {
    this->unitSprites.spaceshipSprite = new Sprite("data\\ship.png",this->window);
    this->unitSprites.smallAsteroidSprite = new Sprite("data\\small.png",this->window);
    this->unitSprites.bigAsteroidSprite = new Sprite("data\\big.png",this->window);
    this->unitSprites.reticleSprite = new Sprite("data\\circle.tga",this->window);
    this->unitSprites.bulletSprite = new Sprite("data\\bullet.png",this->window);
}

void Map::destroySprites() {
    delete this->unitSprites.bigAsteroidSprite;
    delete this->unitSprites.smallAsteroidSprite;
    delete this->unitSprites.spaceshipSprite;
    delete this->unitSprites.reticleSprite;
    delete this->unitSprites.bulletSprite;
}

UnitSprites &Map::getUnitSprites() {
    return this->unitSprites;
}
