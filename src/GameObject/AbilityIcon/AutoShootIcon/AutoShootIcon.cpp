//
// Created by Евгений on 10.10.2022.
//

#include "AutoShootIcon.h"

AutoShootIcon::AutoShootIcon(Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : AbilityIcon(coord, {0, 0}, textureID, textureManager, map) {
    this->map = map;
    this->xyOffset = map->getXY();
}

Ability AutoShootIcon::getAbility() const {
    return AUTOSHOOT;
}