#pragma once

#include <cmath>
#include "../Sprite/Sprite.h"
#include "../Vector2D/Vector2D.h"

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
    MapSprites sprites;
    UnitSprites unitSprites;
    GameWindow* window;
    bool isNeedDeAcc;

    void createMapSprites();
    void createSprites();
    void destroySprites();
    void drawBackground();
    void drawBorder();
public:
	Map(int wMap, int HMap, GameWindow* window);
	~Map();
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
    UnitSprites& getUnitSprites();
    void setIsNeededDeAcc(bool state);
    void render();
    void update();

};