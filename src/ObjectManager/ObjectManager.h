#pragma once

#include <ctime>
#include <vector>
#include "../GameWindow/GameWindow.h"
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
    Velocity randomizeVelocity();
    void createPlayer();
    void createAsteroids();
public:
    ObjectManager(GameWindow* window);
    ~ObjectManager();
    void setNumAsteroids(int amount);
    int getNumAsteroids() const;
    int getAmmoLimit() const;
    std::vector<MovableGameObject*>& getObjects();
    void render();
    void update();
};
