#pragma once

#include <ctime>
#include <vector>
#include "../GameWindow/GameWindow.h"
#include "../Map/Map.h"
#include "../GameObject/SpaceShip.h"
#include "../GameObject/Asteroid.h"

class ObjectManager {
private:
    GameWindow* window;
    Map* map;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    std::vector<GameObject*> gameObjects;
    Vector2D randomizeAppearCoord(int wWindow, int hWindow, int wMap, int hMap);
    Velocity randomizeVelocity(int minVelocity, int maxVelocity, int angleRange);
    void createPlayer();
    void createAsteroids();
public:
    ObjectManager(GameWindow* window, Map* map, int asteroidsLimit, int ammoLimit);
    ~ObjectManager();
    std::vector<GameObject*>& getObjects();
    int getAmmoLimit() const;
    int getNumAsteroids() const;
    void setNumAsteroids(int amount);
    void render();
    void update();
};
