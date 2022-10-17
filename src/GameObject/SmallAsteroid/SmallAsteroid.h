//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include <set>
#include "../GameObject.h"
#include "../../AbilityAppearance/AbilityAppearance.h"
#include "../Missile/Missile.h"

class SmallAsteroid : public GameObject {
private:
    std::set<Missile*>* observers;
    Map* map;
    AbilityAppearance abilityAppearance;
    LimitatorXY limitator;
public:
    SmallAsteroid (Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    ~SmallAsteroid() override;
    void createAbility(std::vector<GameObject*>& buffs);
    void attachObservers(Missile* obs);
    void notExistNotify();
    void update() override;
};