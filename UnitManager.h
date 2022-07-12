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
    Avatar* avatar;
    std::vector<GameObject*> asteroids;
    Game* game;

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
    std::vector<GameObject*>& getAsteroidsVector();

    void checkCollisions();
    void calcOffset();

    Avatar* getAvatar() const;
    void createAvatar();
    void makeShoot();
    void deAcceleration();
    void setIsNeededDeacc(bool state);
};
