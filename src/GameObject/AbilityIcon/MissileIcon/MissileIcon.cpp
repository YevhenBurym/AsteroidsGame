//
// Created by Евгений on 10.10.2022.
//

#include "MissileIcon.h"

MissileIcon::MissileIcon (Vector2D coord, std::string textureID, TextureManager* textureManager, Map* map) : AbilityIcon(coord, {0, 0}, textureID, textureManager, map) {
    this->map = map;
    this->xyOffset = map->getXY();
}

Ability MissileIcon::getAbility() const {
    return MISSILE;
}