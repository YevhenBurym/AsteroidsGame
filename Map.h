#pragma once

#include <cmath>

struct CoordXY {
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
	CoordXY xyRelative;
	Velocity V;
	int Vx,Vy;
	CoordXY offset;
public:
	Map(int wMap, int HMap, int hScreen, int wScreen);
	void calcCoord(double Vx, double Vy, double step);
	int getHMap() const;
	int getWMap() const;
	CoordXY getMapOffsetCoord() const;
	void setMapOffsetX(int x);
	void setMapOffsetY(int y);
	void setX(double x);
	void setY(double y);
	void setV(double v, double theta);
	double getX() const;
	double getY() const;
	double getVx() const;
	double getVy() const;
	Velocity getV() const;
};