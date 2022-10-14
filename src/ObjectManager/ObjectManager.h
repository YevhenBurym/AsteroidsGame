#pragma once

#include <vector>
#include "../GameWindow/GameWindow.h"
#include "../GameObject/SpaceShip/SpaceShip.h"
#include "../GameObject/SmallAsteroid/SmallAsteroid.h"
#include "../GameObject/BigAsteroid/BigAsteroid.h"

class ObjectManager {
private:
    GameWindow* window;
    Map* map;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    SpaceShip* player;
    std::vector<GameObject*> asteroids;
    std::vector<GameObject*> bullets;
    std::vector<GameObject*> buffs;
    RandGenerator randGenerator;
    Vector2D randomizeAppearCoord();
    Vector2D randomizeVelocity();
    void createPlayer();
    void createAsteroids();
public:
    explicit ObjectManager(GameWindow* window);
    ~ObjectManager();
    void setNumAsteroids(int amount);
    int getNumAsteroids() const;
    int getAmmoLimit() const;
    double getAbilityProbability() const;
    std::vector<GameObject*>& getAsteroids();
    std::vector<GameObject*>& getBullets();
    std::vector<GameObject*>& getBuffs();
    SpaceShip* getPlayer();
    void render();
    void update();
};
