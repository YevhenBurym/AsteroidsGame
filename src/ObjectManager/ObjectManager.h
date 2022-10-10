#pragma once

#include <vector>
#include "../GameWindow/GameWindow.h"
#include "../GameObject/MovableGameObject/SpaceShip/SpaceShip.h"
#include "../GameObject/MovableGameObject/SmallAsteroid/SmallAsteroid.h"
#include "../GameObject/MovableGameObject/BigAsteroid/BigAsteroid.h"

class ObjectManager {
private:
    GameWindow* window;
    Map* map;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    SpaceShip* player;
    std::vector<MovableGameObject*> asteroids;
    std::vector<MovableGameObject*> bullets;
    std::vector<MovableGameObject*> buffs;
    RandGenerator randGenerator;
    Vector2D randomizeAppearCoord();
    Velocity randomizeVelocity();
    void createPlayer();
    void createAsteroids();
public:
    explicit ObjectManager(GameWindow* window);
    ~ObjectManager();
    void setNumAsteroids(int amount);
    int getNumAsteroids() const;
    int getAmmoLimit() const;
    double getAbilityProbability() const;
    std::vector<MovableGameObject*>& getAsteroids();
    std::vector<MovableGameObject*>& getBullets();
    std::vector<MovableGameObject*>& getBuffs();
    SpaceShip* getPlayer();
    void render();
    void update();
};
