//
// Created by Евгений on 11.10.2022.
//

#include "AbilityAppearance.h"
#include "../GameObject/AbilityObjects/ShieldObject/ShieldObject.h"
#include "../GameObject/AbilityObjects/MissileObject/MissileObject.h"
#include "../GameObject/AbilityObjects/AutoShootObject/AutoShootObject.h"

AbilityAppearance::AbilityAppearance(TextureManager* textureManager, Map* map) {
    this->generator = RandGenerator();
    this->textureManager = textureManager;
    this->map = map;
}

void AbilityAppearance::createAbility(Vector2D XYAppear, std::vector<GameObject*>& buffs) {
    double randomAbility = this->generator.getRandNumber();

    if (this->generator.getRandNumber() <= 0.3) {
        if (randomAbility <= 0.35) {
            buffs.push_back(new ShieldObject(XYAppear, "shield_ability", this->textureManager, this->map));
        } else if (randomAbility <= 0.65) {
            buffs.push_back(new MissileObject(XYAppear, "missile_ability", this->textureManager, this->map));
        } else {
            buffs.push_back(new AutoShootObject(XYAppear, "autoshoot_ability", this->textureManager, this->map));
        }
    }
}