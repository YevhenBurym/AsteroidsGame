//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../MovableGameObject.h"
#include "../Bullet/Bullet.h"
#include "../../Reticle/Reticle.h"

class SpaceShip : public MovableGameObject {
private:
    InputHandler* inputHandler;
    Reticle* reticle;
    std::vector<MovableGameObject*>* bullets;
    double angleShip;
    int ammoLimit;
    int numBullets;
    bool buttonLeftPress;
    void limitateCoord() override;
public:
    SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager,
              int ammoLimit, Map* map, InputHandler* inputHandler, std::vector<MovableGameObject*>* bullets);
    ~SpaceShip() override;
    void render() const override;
    Vector2D getXYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<MovableGameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
    void update() override;
};