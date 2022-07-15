#pragma once

#include "Map.h"
#include "Window.h"
#include "Sprite.h"
#include <vector>

#define RAD 3.14/180

class GameObject {
protected:
    Vector2D coord;
    Velocity V;
    Vector2D Vxy;
    double xOf, yOf;
    double mass;
    double radius;
    Sprite* sprite;
    Map* map;
    virtual void limitateCoord();
public:
    GameObject(Vector2D coord, double velocity, double theta, Sprite* sprite, Map* map);
    virtual ~GameObject() = default;
    virtual void calcCoord(Vector2D Vxy, double step);
    virtual void setX(double x);
    virtual void setY(double y);
    virtual void setXof(double x);
    virtual void setYof(double y);
    virtual void setVxy(Vector2D vxy);
    virtual void setV(double v, double theta);
    virtual double getX() const;
    virtual double getY() const;
    virtual double getXrel() const;
    virtual double getYrel() const;
    virtual Vector2D getVxy() const;
    virtual Velocity getV() const;
    virtual double getMass() const;
    virtual double getRadius() const;
    virtual void render() const;
};

class SmallAsteroid : public GameObject {
public:
    SmallAsteroid (Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map);
};

class BigAsteroid : public GameObject {
public:
    BigAsteroid(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map);
    void divide(std::vector<GameObject*>& objects);
};

class Bullet : public GameObject {
public:
    Bullet(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map);
};

class Reticle : public GameObject {
public:
    Reticle(Sprite* sprite, Map* map);
    void render() const override;
};

class Avatar : public GameObject {
private:
    Reticle* reticle;
    double angleShip;
    int ammoLimit;
    int numBullets;
    void limitateCoord() override;
public:
    Avatar(Vector2D coord, int velocity, int theta, Sprite* sprite, int ammoLimit, Map* map);
    ~Avatar() override;
    void render() const override;
    double getXrel() const override;
    double getYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<GameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
};

