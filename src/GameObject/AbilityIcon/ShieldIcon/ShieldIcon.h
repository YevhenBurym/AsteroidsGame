//
// Created by Евгений on 10.10.2022.
//

#pragma once

#include "../AbilityIcon.h"

class ShieldIcon: public AbilityIcon {
public:
    ShieldIcon(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map);
    Ability getAbility() const override;
};
