//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "Map.h"
#include "AsteroidsManager.h"
#include "InputComponent.h"
#include "Collisions.h"
#include "SpaceShip.h"
#include "Asteroid.h"

class AsteroidsManager;
class InputComponent;
class Collisions;

class Game {
private:
    SpaceShip* ship;
    InputComponent* inputHandler;
    Collisions* collisions;
    Map* map;
    Window* gameWindow;
    AsteroidsManager* asterManager;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
    bool quit;
    std::vector<GameObject*> gameObjects;
    void createPlayer();
    void renderObjects();
    void calcObjectOffset();
public:
    Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    ~Game();
    bool init();
    void handleEvents();
    void update();
    void render();

    void close();

    void restart();

    Map* getMap() const;
    Window* getWindow() const;
    AsteroidsManager* getAsterManager() const;
    int getAmmoLimit() const;
    int getAsteroidslimit() const;
    std::vector<GameObject*>& getObjects();
    SpaceShip* getPlayer() const;

    void runGame();
};