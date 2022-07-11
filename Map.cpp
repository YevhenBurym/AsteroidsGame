#include "Map.h"

Map::Map(int wMap, int hMap, int hScreen, int wScreen) {
	this->hMap = hMap;
	this->wMap = wMap;
	this->offset.x = wMap / 2 - wScreen / 2;
	this->offset.y = hMap / 2 - hScreen / 2;
	this->xyRelative.x = 0;
	this->xyRelative.y = 0;
	this->V.v = 0;
	this->V.theta = 0;
	this->Vx = 0;
	this->Vy = 0;
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

void Map::setMapOffsetX(int x) {
	this->offset.x = x;
}

void Map::setMapOffsetY(int y) {
	this->offset.y = y;
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