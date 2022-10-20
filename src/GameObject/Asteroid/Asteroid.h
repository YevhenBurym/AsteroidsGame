//
// Created by Евгений on 20.10.2022.
//

#pragma once

#include <set>
#include "../GameObject.h"
#include "../Missile/Missile.h"
#include "../../AbilityAppearance/AbilityAppearance.h"

class Asteroid: public GameObject {
protected:
    std::set<Missile*>* observers;
    Map* map;
    AbilityAppearance abilityAppearance;
    LimitatorXY limitator;
public:
    Asteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager* textureManager, Map* map);
    ~Asteroid() override = 0;
    virtual void createAbility(std::vector<AbilityIcon*>& buffs);
    virtual void attachObservers(Missile* obs);
    virtual void notExistNotify();
    void update() override;
};

