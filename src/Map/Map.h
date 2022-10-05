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
	float Vx,Vy;
	Vector2D offset;
    GameWindow* window;
    bool isNeedDeAcc;

    void drawBackground();
    void drawBorder();
public:
	Map(GameWindow* window);
	~Map() = default;
	void calcCoord(double Vx, double Vy, double step);
	int getHMap() const;
	int getWMap() const;
	Vector2D getMapOffsetCoord() const;
    void mapInit();
	void setX(double x);
	void setY(double y);
    void setVx(double vx);
    void setVy(double vy);
	double getX() const;
	double getY() const;
	double getVx() const;
	double getVy() const;
    void setIsNeededDeAcc(bool state);
    void render();
    void update();

};