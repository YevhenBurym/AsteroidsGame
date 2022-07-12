#pragma once

#include "GameObject.h"
#include <vector>
#include <cstdint>
#include <time.h>
#include "Game.h"
#include "Window.h"
class Game;

class UnitManager {
    bool isNeedDeAcc;
    Avatar* avatar;
    Game* game;
public:
    UnitManager(Game* game);
    ~UnitManager();

    void createAsteroids();
    CoordXY randomizeAppearCoord(int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void drawAsteroids();

    void calcOffset();

    Avatar* getAvatar() const;
    void createAvatar();
    void makeShoot();
    void deAcceleration();
    void setIsNeededDeacc(bool state);
};
