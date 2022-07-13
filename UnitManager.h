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
    Game* game;
public:
    UnitManager(Game* game);

    void createAsteroids();
    CoordXY randomizeAppearCoord(int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);

    void deAcceleration();
    void setIsNeededDeacc(bool state);
};
