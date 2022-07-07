#pragma once

#include "MoveableUnit.h"
#include <vector>
#include <cstdint>
#include <time.h>
#include "GameManager.h"
#include "AsteroidsGame.h"
#include "GameWindow.h"

struct UnitSprites {
    Sprite* bigAsteroidSprite;
    Sprite* smallAsteroidSprite;
    Sprite* spaceshipSprite;
    Sprite* reticleSprite;
    Sprite* bulletSprite;
};


class AsteroidsGame;

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
    AsteroidsGame* game;
    double angleShip;

    void createSprites();
    void destroySprites();
    void fixCoordAfterCollision(MoveableUnit* unit1, MoveableUnit* unit2, CoordXY vectorBetween);
    void calcVelocityAfterCollision(MoveableUnit* unit1, MoveableUnit* unit2, CoordXY vectorBetween);
public:
    UnitManager(int asteroidsLimit, int bulletsLimit, int maxVelocity, AsteroidsGame* game);
    ~UnitManager();
    void createAsteroids();
    void createAvatar();
    std::vector<MoveableUnit*>& getAsteroidsVector();
    CoordXY randomizeAppearCoord(int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void drawAsteroids();
    void drawReticle();
    void shipHeadAngle();
    void makeShoot();
    void divideBigAsteroid(BigAsteroid* asteroid);
    void deAcceleration();
    void checkCollisions();
    void calcOffset();
    int getNumAsteroids() const;
    int getNumBullets() const;
    void setNumAsteroids(int num);
    void setNumBullets(int num);
    void setXReticle(int x);
    void setYReticle(int y);
    void setIsNeededDeacc(bool state);
};
