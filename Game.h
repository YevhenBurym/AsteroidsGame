//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "Map.h"
#include "UnitManager.h"
#include "InputHandler.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX
#define PI 3.14159

struct MapSprites {
    Sprite* backgroundSprite;
    Sprite* dotSprite;
};

class UnitManager;
class InputHandler;

class Game {
private:
    InputHandler* inputHandler;
    Map* map;
    Window* gameWindow;
    UnitManager* unitManager;
    MapSprites sprites;
    int hScreen, wScreen;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;

    void createSprites();
    void drawBackground();
    void drawMapBorder();
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