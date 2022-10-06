//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "MovableGameObject.h"

class Bullet : public MovableGameObject {
public:
    Bullet(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map);
};

class Reticle : public MovableGameObject {
public:
    Reticle(std::string textureID, TextureManager* textureManager, Map* map);
    void render() const override;
};

class SpaceShip : public MovableGameObject {
private:
    Reticle* reticle;
    double angleShip;
    int ammoLimit;
    int numBullets;
    InputComponent* inputHandler;
    std::vector<MovableGameObject*>* gameObjects;
    bool buttonLeftPress;
    void limitateCoord() override;
public:
    SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager,
            int ammoLimit, Map* map, InputComponent* inputHandler, std::vector<MovableGameObject*>* objects);
    ~SpaceShip() override;
    void render() const override;
    double getXrel() const override;
    double getYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<MovableGameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
    void update() override;
};