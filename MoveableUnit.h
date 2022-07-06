#pragma once

#include "GameManager.h"
#include "Map.h"

#define RAD 3.14/180

class MoveableUnit1 {
protected:
    double x, y;
    double xOf, yOf;
    double mass;
    double Vx, Vy;
    double radius;
    Velocity V;
    SDL_Texture * sprite;
    Map* map;
    virtual void limitateCoord();
public:
    MoveableUnit1(double x, double y, double velocity, double theta, SDL_Texture* sprite, Map* map);
    virtual ~MoveableUnit1() = default;
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
    virtual SDL_Texture* getSprite() const;
};

class SmallAsteroid1 : public MoveableUnit1 {
public:
    SmallAsteroid1 (double x, double y, int velocity, int theta, SDL_Texture* sprite, Map* map);
};

class BigAsteroid1 : public MoveableUnit1 {
public:
    BigAsteroid1(double x, double y, int velocity, int theta, SDL_Texture* sprite, Map* map);
};

class Avatar1 : public MoveableUnit1 {
private:
    void limitateCoord() override;
public:
    Avatar1(double x, double y, int velocity, int theta, SDL_Texture* sprite, Map* map);
    double getXrel() const override;
    double getYrel() const override;
};
class Bullet1 : public MoveableUnit1 {
public:
    Bullet1(double x, double y, int velocity, int theta, SDL_Texture* sprite, Map* map);
};