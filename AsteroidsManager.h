#pragma once

#include <ctime>
#include "Game.h"

class Game;

class AsteroidsManager {
private:
    Game* game;
    CoordXY randomizeAppearCoord(int wWindow, int hWindow, int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
public:
    AsteroidsManager(Game* game);
    void createAsteroids();

};
