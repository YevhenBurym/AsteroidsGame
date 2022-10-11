//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../GameObject.h"
#include "../Bullet/Bullet.h"
#include "../Reticle/Reticle.h"

class SpaceShip : public GameObject {
private:
    Map* map;
    InputHandler* inputHandler;
    Reticle* reticle;
    std::vector<GameObject*>* bullets;
    double angleShip;
    int ammoLimit;
    int numBullets;
    bool buttonLeftPress;
    void limitateXY();
public:
    SpaceShip(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager,
              int ammoLimit, Map* map, InputHandler* inputHandler, std::vector<GameObject*>* bullets);
    ~SpaceShip() override;

    Vector2D getXYrel() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot(std::vector<GameObject*>& objects);
    int getNumBullets() const;
    void setNumBullets(int amount);
    void update() override;
    void render() override;
};