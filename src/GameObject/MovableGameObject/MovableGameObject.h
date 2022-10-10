//
// Created by Евгений on 03.10.2022.
//

#pragma once
#include "../GameObject.h"
#include "../../Map/Map.h"

class MovableGameObject: public GameObject {
protected:
    Map* map;
    Velocity V;
    Vector2D Vxy;
    Vector2D acceleration;
    double xOf, yOf;
    double mass;
    double radius;

    virtual void limitateCoord();
    virtual void calcCoord();
public:
    MovableGameObject(Vector2D coord, double velocity, double theta,
            std::string textureID, TextureManager* textureManager, Map* map);
    ~MovableGameObject() override = 0;
    virtual void setVxy(Vector2D vxy);
    virtual Vector2D getXYrel() const;
    virtual Vector2D getVxy() const;
    virtual double getMass() const;
    virtual double getRadius() const;
    virtual void render() const;
    void update() override;
};


