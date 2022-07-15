#pragma once

#include <cmath>
#include "Sprite.h"

struct MapSprites {
    Sprite* backgroundSprite;
    Sprite* dotSprite;
};

struct UnitSprites {
    Sprite* bigAsteroidSprite;
    Sprite* smallAsteroidSprite;
    Sprite* spaceshipSprite;
    Sprite* reticleSprite;
    Sprite* bulletSprite;
};

struct Vector2D {
	double x;
	double y;
};

struct Velocity {
	double v;
	double theta;
};

class Map {
private:
	int hMap, wMap;
	Vector2D xyRelative;
	Velocity V;
	int Vx,Vy;
	Vector2D offset;
    MapSprites sprites;
    UnitSprites unitSprites;
    Window* window;
    bool isNeedDeAcc;

    void createMapSprites();
    void createSprites();
    void destroySprites();
    void drawBackground();
    void drawBorder();
public:
	Map(int wMap, int HMap, Window* window);
	~Map();
	void calcCoord(double Vx, double Vy, double step);
	int getHMap() const;
	int getWMap() const;
	Vector2D getMapOffsetCoord() const;
    void mapInit();
	void setX(double x);
	void setY(double y);
	void setV(double v, double theta);
    void setVx(double vx);
    void setVy(double vy);
	double getX() const;
	double getY() const;
	double getVx() const;
	double getVy() const;
	Velocity getV() const;
    void draw();
    UnitSprites& getUnitSprites();
    void deAcceleration();
    void setIsNeededDeacc(bool state);
};