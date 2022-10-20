//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../AbilityIcon.h"

class AutoShootIcon: public AbilityIcon {
public:
    AutoShootIcon(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
    Ability getAbility() const override;
};

