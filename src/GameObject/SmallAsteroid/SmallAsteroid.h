//
// Created by Евгений on 16.07.2022.
//

#pragma once

#include "../GameObject.h"
#include "../../AbilityAppearance/AbilityAppearance.h"

class SmallAsteroid : public GameObject {
private:
    Map* map;
    AbilityAppearance abilityAppearance;
    LimitatorXY limitator;
public:
    SmallAsteroid (Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    void createAbility(std::vector<GameObject*>& buffs);
    void update() override;
};