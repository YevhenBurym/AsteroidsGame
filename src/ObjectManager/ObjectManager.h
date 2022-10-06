#pragma once

#include <ctime>
#include <vector>
#include "../GameWindow/GameWindow.h"
#include "../Map/Map.h"
#include "../GameObject/MovableGameObject/SpaceShip/SpaceShip.h"
#include "../GameObject/MovableGameObject/SmallAsteroid/SmallAsteroid.h"
#include "../GameObject/MovableGameObject/BigAsteroid/BigAsteroid.h"

class ObjectManager {
private:
    GameWindow* window;
    Map* map;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    std::vector<MovableGameObject*> gameObjects;
    Vector2D randomizeAppearCoord();
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void createPlayer();
    void createAsteroids();
public:
    ObjectManager(GameWindow* window/*, Map* map*/);
    ~ObjectManager();
    std::vector<MovableGameObject*>& getObjects();
    int getAmmoLimit() const;
    int getNumAsteroids() const;
    void setNumAsteroids(int amount);
    void render();
    void update();
};
