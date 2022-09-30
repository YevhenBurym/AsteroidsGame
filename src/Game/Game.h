//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "../Map/Map.h"
#include "../ObjectManager/ObjectManager.h"
#include "../InputComponent/InputComponent.h"
#include "../Collisions/Collisions.h"



class Game {
private:
    InputComponent* inputHandler;
    Collisions* collisions;
    Map* map;
    GameWindow* gameWindow;
    ObjectManager* objectManager;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
public:
    Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    ~Game();
    bool init();
    void update();
    void render();
    void close();
    void restart();
    void run();
};