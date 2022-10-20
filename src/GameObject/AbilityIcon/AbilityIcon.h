//
// Created by Евгений on 20.10.2022.
//

#pragma once

#include <chrono>
#include "../GameObject.h"

enum Ability {
    SHIELD,
    MISSILE,
    AUTOSHOOT,
    NONE
};

class AbilityIcon: public GameObject {
protected:
    Map* map;
    int existingDuration;
    std::chrono::high_resolution_clock::time_point startExistingTimer, endExistingTimer;
    bool isExist;
public:
    AbilityIcon(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    void update() override;
    bool getIsExist() const;
    virtual Ability getAbility() const = 0;
};

