#pragma once

#include <ctime>

#include "../Game/Game.h"

class Game;

class AsteroidsManager {
private:
    Game* game;
    int asteroidsLimit;
    int numAsteroids;
    Vector2D randomizeAppearCoord(int wWindow, int hWindow, int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
public:
    AsteroidsManager(Game* game);
    void createAsteroids();
    int getAsteroidslimit() const;
    int getNumAsteroids() const;
    void setNumAsteroids(int amount);

};
