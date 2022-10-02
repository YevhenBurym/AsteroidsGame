#pragma once

#include "../Map/Map.h"
#include <vector>
#include <cmath>

#define RAD 3.14/180

class GameObject {
protected:
    Vector2D coord;
    Velocity V;
    Vector2D Vxy;
    Vector2D acceleration;
    double xOf, yOf;
    double mass;
    double radius;
    std::string textureID;
    int wSprite, hSprite;
    TextureManager* textureManager;
    Map* map;
    virtual void limitateCoord();
public:
    GameObject(Vector2D coord, double velocity, double theta, std::string textureID, TextureManager* textureManager, Map* map);
    virtual ~GameObject() = default;
    virtual void calcCoord(Vector2D Vxy, double step);
    virtual void setX(double x);
    virtual void setY(double y);
    virtual void setXof(double x);
    virtual void setYof(double y);
    virtual void setVxy(Vector2D vxy);
    virtual double getX() const;
    virtual double getY() const;
    virtual double getXrel() const;
    virtual double getYrel() const;
    virtual Vector2D getVxy() const;
    virtual double getMass() const;
    virtual double getRadius() const;
    virtual void render() const;
};