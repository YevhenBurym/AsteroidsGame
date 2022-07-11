#pragma once

#include "Map.h"
#include "Window.h"
#include "Sprite.h"

#define RAD 3.14/180

class MoveableUnit {
protected:
    double x, y;
    double xOf, yOf;
    double mass;
    double Vx, Vy;
    double radius;
    Velocity V;
    Sprite * sprite;
    Map* map;
    virtual void limitateCoord();
public:
    MoveableUnit(double x, double y, double velocity, double theta, Sprite* sprite, Map* map);
    virtual ~MoveableUnit() = default;
    virtual void calcCoord(double Vx, double Vy, double step);
    virtual void setX(double x);
    virtual void setY(double y);
    virtual void setXof(double x);
    virtual void setYof(double y);
    virtual void setVx(double vx);
    virtual void setVy(double vy);
    virtual void setV(double v, double theta);
    virtual double getX() const;
    virtual double getY() const;
    virtual double getXrel() const;
    virtual double getYrel() const;
    virtual double getVx() const;
    virtual double getVy() const;
    virtual Velocity getV() const;
    virtual double getMass() const;
    virtual double getRadius() const;
    virtual Sprite* getSprite() const;
    virtual void draw() const;
};

class SmallAsteroid : public MoveableUnit {
public:
    SmallAsteroid (double x, double y, int velocity, int theta, Sprite* sprite, Map* map);
};

class BigAsteroid : public MoveableUnit {
public:
    BigAsteroid(double x, double y, int velocity, int theta, Sprite* sprite, Map* map);
    //SmallAsteroid* divide();
};

class Avatar : public MoveableUnit {
private:
    void limitateCoord() override;
public:
    Avatar(double x, double y, int velocity, int theta, Sprite* sprite, Map* map);
    double getXrel() const override;
    double getYrel() const override;
};
class Bullet : public MoveableUnit {
public:
    Bullet(double x, double y, int velocity, int theta, Sprite* sprite, Map* map);
};