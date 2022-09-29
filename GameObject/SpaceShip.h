//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "GameObject.h"

class Bullet : public GameObject {
public:
    Bullet(Vector2D coord, int velocity, int theta, Sprite* sprite, Map* map);
};

class Reticle : public GameObject {
public:
    Reticle(Sprite* sprite, Map* map);
    void render() const override;
};

class SpaceShip : public GameObject {
private:
    Reticle* reticle;
    double angleShip;
    int ammoLimit;
    int numBullets;
    void limitateCoord() override;
public:
    SpaceShip(Vector2D coord, int velocity, int theta, Sprite* sprite, int ammoLimit, Map* map);
    ~SpaceShip() override;
    void render() const override;
    double getXrel() const override;
    double getYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<GameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
};