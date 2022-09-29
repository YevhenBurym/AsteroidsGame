//
// Created by Евгений on 04.07.2022.
//

#pragma once

#include "../Map/Map.h"
#include "../AsteroidManager/AsteroidsManager.h"
#include "../InputComponent/InputComponent.h"
#include "../Collisions/Collisions.h"

class AsteroidsManager;
class InputComponent;
class Collisions;
class SpaceShip;
class GameObject;
//class SmallAsteroid;
//class BigAsteroid;

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int hWindow, wWindow;


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
    bool initWindow(const char* name, int width, int height, bool isFullscreen);
public:
    Game(int wScreen, int hScreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability);
    ~Game();
    bool init();
    void handleEvents();
    void update();
    void render();

    void close();
    void clean();

    void restart();
    void setQuit(bool quit);
    SDL_Renderer* getRenderer() const;
    Map* getMap() const;
    Window* getWindow() const;
    AsteroidsManager* getAsterManager() const;
    int getAmmoLimit() const;
    int getAsteroidslimit() const;
    std::vector<GameObject*>& getObjects();
    SpaceShip* getPlayer() const;

    void runGame();
};