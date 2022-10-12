//
// Created by Евгений on 11.10.2022.
//

#pragma once

#include "../GameObject/GameObject.h"
#include "../RandomGenerator/RandomGenerator.h"

class AbilityAppearance {
private:
    TextureManager* textureManager;
    Map* map;
    RandGenerator generator;
public:
    AbilityAppearance(TextureManager* textureManager, Map* map);
    void createAbility(Vector2D XYAppear, std::vector<GameObject*>& buffs);
};

