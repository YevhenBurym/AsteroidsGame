//
// Created by Евгений on 03.10.2022.
//

#pragma once

#include "../Map/Map.h"

class LimitatorXY {
private:
  Map* map;
public:
    explicit LimitatorXY(Map* map);
    void limitateXY(Vector2D& currXY);
};

class GameObject {
protected:
    TextureManager* textureManager;
    std::string textureID;
    int wSprite, hSprite;
    Vector2D coord;
    //Map* map;
    Velocity V;
    Vector2D Vxy;
    Vector2D acceleration;
    double xOf, yOf;
    double mass;
    double radius;
    virtual void calcCoord();
public:
    GameObject(Vector2D coord, double velocity, double theta,
               std::string textureID, TextureManager* textureManager);
    virtual ~GameObject();
    virtual void setXY(Vector2D newXY);
    virtual Vector2D getXY() const;
    virtual void setVxy(Vector2D vxy);
    virtual Vector2D getXYrel() const;
    virtual Vector2D getVxy() const;
    virtual double getMass() const;
    virtual double getRadius() const;
    virtual void render();
    virtual void update();
};


