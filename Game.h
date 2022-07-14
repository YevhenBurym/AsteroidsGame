//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "Map.h"
#include "AsteroidsManager.h"
#include "InputComponent.h"
#include "Collisions.h"

class AsteroidsManager;
class InputComponent;
class Collisions;

class Game {
private:
    Avatar* avatar;
    InputComponent* inputHandler;
    Collisions* collisions;
    Map* map;
    Window* gameWindow;
    AsteroidsManager* asterManager;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
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
    Window* getWindow() const;
    AsteroidsManager* getAsterManager() const;
    int getAmmoLimit() const;
    int getAsteroidslimit() const;
    int getNumAsteroids() const;
    void setNumAsteroids(int amount);
    std::vector<GameObject*>& getObjects();
    Avatar* getAvatar() const;
    void runGame();
};