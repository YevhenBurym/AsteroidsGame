#pragma once

#include <cmath>
#include "../Vector2D/Vector2D.h"
#include "../GameWindow/GameWindow.h"

struct Velocity {
	double v;
	double theta;
};

class Map {
private:
	int hMap, wMap;
	Vector2D xyRelative;
    Vector2D Vxy;
	Vector2D offset;
    GameWindow* window;
    bool isNeedDeAcc;

    void drawBackground();
    void drawBorder();
public:
	Map(GameWindow* window);
	~Map() = default;
	void calcCoord();
	int getHMap() const;
	int getWMap() const;
	Vector2D getMapOffsetCoord() const;
    void mapInit();
	void setX(double x);
	void setY(double y);
	Vector2D getXY() const;
	Vector2D getVxy() const;
    void render();
    void update();

};