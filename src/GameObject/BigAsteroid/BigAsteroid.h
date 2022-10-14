//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../GameObject.h"
#include "../SmallAsteroid/SmallAsteroid.h"
#include "../../AbilityAppearance/AbilityAppearance.h"

class BigAsteroid : public GameObject {
private:
    Map* map;
    AbilityAppearance abilityAppearance;
    LimitatorXY limitator;
public:
    BigAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    void divide(std::vector<GameObject*>& objects);
    void createAbility(std::vector<GameObject*>& buffs);
    void update() override;
};
