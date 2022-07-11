//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "Map.h"
#include "UnitManager.h"
#include "InputComponent.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX
#define PI 3.14159

class UnitManager;
class InputComponent;

class Game {
private:
    InputComponent* inputHandler;
    Map* map;
    Window* gameWindow;
    UnitManager* unitManager;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
public:
    Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    bool init();
    void close();
    bool tick();

    void restart();
    Map* getMap() const;
    UnitManager* getUnitManager() const;
    Window* getWindow() const;
    void runGame();
};