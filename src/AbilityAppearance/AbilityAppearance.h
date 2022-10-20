//
// Created by Евгений on 11.10.2022.
//

#pragma once

#include "../RandomGenerator/RandomGenerator.h"
#include "../GameObject/AbilityIcon/MissileIcon/MissileIcon.h"
#include "../GameObject/AbilityIcon/AutoShootIcon/AutoShootIcon.h"
#include "../GameObject/AbilityIcon/ShieldIcon/ShieldIcon.h"

class AbilityAppearance {
private:
    TextureManager* textureManager;
    Map* map;
    RandGenerator generator;
public:
    AbilityAppearance(TextureManager* textureManager, Map* map);
    void createAbility(Vector2D XYAppear, std::vector<AbilityIcon*>& buffs);
};

