//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../AbilityIcon.h"

class MissileIcon: public AbilityIcon {
public:
    MissileIcon(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
    Ability getAbility() const override;
};
