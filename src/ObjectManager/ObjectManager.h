#pragma once

#include <vector>
#include "../GameWindow/GameWindow.h"
#include "../GameObject/SpaceShip/SpaceShip.h"
#include "../GameObject/Asteroid/SmallAsteroid/SmallAsteroid.h"
#include "../GameObject/Asteroid/BigAsteroid/BigAsteroid.h"
#include "../GameObject/AbilityIcon/AbilityIcon.h"

class ObjectManager {
private:
    GameWindow* window;
    Map* map;
    int asteroidsLimit;
    int ammoLimit;
    int numAsteroids;
    SpaceShip* player;
    std::vector<Asteroid*> asteroids;
    std::vector<GameObject*> bullets;
    std::vector<AbilityIcon*> buffs;
    RandGenerator randGenerator;
    Vector2D randomizeAppearCoord();
    Vector2D randomizeVelocity();
    void createPlayer();
    void createAsteroids();
    int destroyedBigAsteroidAmount;
    int destroyedSmallAsteroidAmount;
public:
    explicit ObjectManager(GameWindow* window);
    ~ObjectManager();
    void setNumAsteroids(int amount);
    void setDestroyedSmallAsteroidsAmount(int amount);
    void setDestroyedBigAsteroidsAmount(int amount);
    int getNumAsteroids() const;
    int getAmmoLimit() const;
    int getDestroyedSmallAsteroidsAmount() const;
    int getDestroyedBigAsteroidsAmount() const;
    std::vector<Asteroid*>& getAsteroids();
    std::vector<GameObject*>& getBullets();
    std::vector<AbilityIcon*>& getBuffs();
    SpaceShip* getPlayer();
    void render();
    void update();
};
