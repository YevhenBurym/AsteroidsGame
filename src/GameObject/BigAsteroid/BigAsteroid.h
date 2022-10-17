//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include <set>
#include "../GameObject.h"
#include "../SmallAsteroid/SmallAsteroid.h"
#include "../../AbilityAppearance/AbilityAppearance.h"
#include "../Missile/Missile.h"

class BigAsteroid : public GameObject {
private:
    std::set<Missile*>* observers;
    Map* map;
    AbilityAppearance abilityAppearance;
    LimitatorXY limitator;
public:
    BigAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    ~BigAsteroid() override;
    void divide(std::vector<GameObject*>& objects);
    void createAbility(std::vector<GameObject*>& buffs);
    void attachObservers(Missile* obs);
    void notExistNotify();
    void update() override;
};
