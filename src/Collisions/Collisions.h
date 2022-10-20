//
// Created by Евгений on 12.07.2022.
//

#pragma once

#include <cmath>
#include "../ObjectManager/ObjectManager.h"

class YouDied {};

class Collisions {
private:
    ObjectManager* objectManager;
    double findVecAngleInRad(Vector2D vector);
    void fixCoord(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
    void calcVelocity(GameObject* unit1, GameObject* unit2, Vector2D vectorBetween);
    void asteroidsCollisions();
    void abilitiesCollisions();
    void asteroidWithPlayerCollisions(Asteroid* asteroid);
    void asteroidWithReticleCollisions(Asteroid* asteroid);
    void asteroidWithBulletsCollisions(std::vector<Asteroid*>::iterator& asteroidIterator);
public:
    explicit Collisions(ObjectManager* objectManager);
    void update();
};
