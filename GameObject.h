#pragma once

#include "Map.h"
#include "Window.h"
#include "Sprite.h"
#include <vector>

#define RAD 3.14/180

class GameObject {
protected:
    CoordXY coord;
    Velocity V;
    double Vx, Vy;
    double xOf, yOf;
    double mass;
    double radius;
    Sprite* sprite;
    Map* map;
    virtual void limitateCoord();
public:
    GameObject(CoordXY coord, double velocity, double theta, Sprite* sprite, Map* map);
    virtual ~GameObject() = default;
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

class SmallAsteroid : public GameObject {
public:
    SmallAsteroid (CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map);
};

class BigAsteroid : public GameObject {
public:
    BigAsteroid(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map);
    void divide(std::vector<GameObject*>& objects);
};

class Bullet : public GameObject {
public:
    Bullet(CoordXY coord, int velocity, int theta, Sprite* sprite, Map* map);
};

class Reticle : public GameObject {
public:
    Reticle(Sprite* sprite, Map* map);
    void draw() const override;
};

class Avatar : public GameObject {
private:
    Reticle* reticle;
    double angleShip;
    int ammoLimit;
    int numBullets;
    void limitateCoord() override;
public:
    Avatar(CoordXY coord, int velocity, int theta, Sprite* sprite, int ammoLimit, Map* map);
    ~Avatar() override;
    void draw() const override;
    double getXrel() const override;
    double getYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<GameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
};

