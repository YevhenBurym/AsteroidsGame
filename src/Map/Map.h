#pragma once

#include <cmath>
#include "../Vector2D/Vector2D.h"
#include "../GameWindow/GameWindow.h"

class Map {
private:
    GameWindow* window;
	int hMap, wMap;
	Vector2D xyRelative;
    Vector2D Vxy
	Vector2D offset;
	Vector2D maxCoord;
	Vector2D minCoord;

    void drawBackground();
    void drawBorder();
    void deAcc();
public:
	Map(GameWindow* window);
	~Map() = default;

	int getHMap() const;
	int getWMap() const;
	Vector2D getMaxCoord() const;
    Vector2D getMinCoord() const;
	Vector2D getOffset() const;
	void setX(double x);
	void setY(double y);
    void setVxy(Vector2D newVxy);
    Vector2D getVxy() const;
	Vector2D getXY() const;
    void render();
    void update();

};