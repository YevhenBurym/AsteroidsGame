//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include <chrono>
#include "../GameObject.h"
#include "../Bullet/Bullet.h"
#include "../Reticle/Reticle.h"

enum Ability {
    SHIELD,
    MISSILE,
    AUTOSHOOT,
    NONE
};

class SpaceShip : public GameObject {
private:
    Map* map;
    InputHandler* inputHandler;
    Reticle* reticle;
    std::vector<GameObject*>* bullets;
    double angleShip;
    int ammoLimit;
    int numBullets;
    bool buttonLeftPress, buttonRightPress;
    Ability ability;

    bool isShieldON;
    int widthShield, heightShield;
    double shieldRadius;
    std::chrono::high_resolution_clock::time_point startTimer, endTimer;

    void useAbility();
    void limitateXY();
public:
    SpaceShip(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager,
              int ammoLimit, Map* map, InputHandler* inputHandler, std::vector<GameObject*>* bullets);
    ~SpaceShip() override;

    Vector2D getXYrel() const override;
    double getRadius() const override;
    void setVxy(Vector2D vxy) override;
    Vector2D getVxy() const override;
    Reticle* getReticle() const;
    void shipHeadAngle();
    void makeShoot();
    int getNumBullets() const;
    void setNumBullets(int amount);
    void setAbility(Ability newAbility);
    bool getIsShieldOn() const;
    void update() override;
    void render() override;
};