//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "GameManager.h"
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

class AsteroidsGame: public Game {
private:
    InputHandler* inputHandler;
    Map* map;
    GameWindow* gameWindow;
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
    AsteroidsGame(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    bool init() override;
    void close() override;
    bool tick() override;

    void restart();
    Map* getMap() const;
    UnitManager* getUnitManager() const;
    GameWindow* getWindow() const;
    void runGame();
};