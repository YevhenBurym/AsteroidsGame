//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "GameManager.h"
#include "Map.h"
#include "UnitManager.h"

#define RANDRANGE_0_1 (double)rand() / RAND_MAX
#define PI 3.14159

struct MapSprites {
    SDL_Texture* backgroundSprite;
    SDL_Texture* dotSprite;
};

class UnitManager;

class AsteroidsGame: public Game {
private:
    Map* map;
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
    void preInit(int& width, int& height, bool& fullscreen) override;
    bool init() override;
    void close() override;
    bool tick() override;
    void onMouseMove(int x, int y, int xrelative, int yrelative) override;
    void onMouseButtonClick(GameMouseButton button, bool isReleased) override;
    void onKeyPressed(GameKey k) override;
    void onKeyReleased(GameKey k) override;
    const char* getTitle() override;
    void restart();
    Map* getMap() const;

};