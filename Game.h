//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "Map.h"
#include "UnitManager.h"
#include "InputComponent.h"
#include "Collisions.h"

class UnitManager;
class InputComponent;
class Collisions;

class Game {
private:
    Avatar* avatar;
    InputComponent* inputHandler;
    Collisions* collisions;
    Map* map;
    Window* gameWindow;
    UnitManager* unitManager;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    std::vector<GameObject*> gameObjects;
    void createAvatar();
    void drawObjects();
    void calcObjectOffset();
public:
    Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    ~Game();
    bool init();
    void close();
    bool tick();

    void restart();
    Map* getMap() const;
    UnitManager* getUnitManager() const;
    Window* getWindow() const;
    int getAmmoLimit() const;
    int getAsteroidslimit() const;
    int getNumAsteroids() const;
    void setNumAsteroids(int amount);
    std::vector<GameObject*>& getObjects();
    Avatar* getAvatar() const;
    void runGame();
};