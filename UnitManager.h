#pragma once

#include "GameObject.h"
#include <vector>
#include <cstdint>
#include <time.h>
#include "Game.h"
#include "Window.h"
class Game;

class UnitManager {
    int asteroidsLimit;
    int bulletsLimit;
    int numAsteroids;
    int numBullets;
    bool isNeedDeAcc;
    //CoordXY reticle;
    //CoordXY reticleOffset;
    Reticle* reticle;
    std::vector<GameObject*> asteroids;
    Game* game;
    double angleShip;

    void fixCoordAfterCollision(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween);
    void calcVelocityAfterCollision(GameObject* unit1, GameObject* unit2, CoordXY vectorBetween);
public:
    UnitManager(int asteroidsLimit, int bulletsLimit, int maxVelocity, Game* game);
    ~UnitManager();

    void createAsteroids();
    CoordXY randomizeAppearCoord(int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void drawAsteroids();
    void divideBigAsteroid(BigAsteroid* asteroid);


    void checkCollisions();
    void calcOffset();

    Reticle* getReticle() const;
    void createAvatar();
    void shipHeadAngle();
    void makeShoot();
    void deAcceleration();
    void setIsNeededDeacc(bool state);
};
