#pragma once

#include "MoveableUnit.h"
#include <vector>
#include <cstdint>
#include <time.h>
#include "Game.h"
#include "Window.h"

struct UnitSprites {
    Sprite* bigAsteroidSprite;
    Sprite* smallAsteroidSprite;
    Sprite* spaceshipSprite;
    Sprite* reticleSprite;
    Sprite* bulletSprite;
};


class Game;

class UnitManager {
    int asteroidsLimit;
    int bulletsLimit;
    int numAsteroids;
    int numBullets;
    bool isNeedDeAcc;
    CoordXY reticle;
    CoordXY reticleOffset;
    UnitSprites sprites;
    std::vector<MoveableUnit*> asteroids;
    Game* game;
    double angleShip;

    void createSprites();
    void destroySprites();
    void fixCoordAfterCollision(MoveableUnit* unit1, MoveableUnit* unit2, CoordXY vectorBetween);
    void calcVelocityAfterCollision(MoveableUnit* unit1, MoveableUnit* unit2, CoordXY vectorBetween);
public:
    UnitManager(int asteroidsLimit, int bulletsLimit, int maxVelocity, Game* game);
    ~UnitManager();
    void createAsteroids();

    std::vector<MoveableUnit*>& getAsteroidsVector();
    CoordXY randomizeAppearCoord(int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void drawAsteroids();

    void divideBigAsteroid(BigAsteroid* asteroid);

    void checkCollisions();
    void calcOffset();
    int getNumAsteroids() const;
    int getNumBullets() const;
    void setNumAsteroids(int num);
    void setNumBullets(int num);


    void drawReticle();
    void setXReticle(int x);
    void setYReticle(int y);


    void createAvatar();
    void shipHeadAngle();
    void makeShoot();
    void deAcceleration();
    void setIsNeededDeacc(bool state);
};
