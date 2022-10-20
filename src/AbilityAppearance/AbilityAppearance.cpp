//
// Created by Евгений on 11.10.2022.
//

#include "AbilityAppearance.h"

AbilityAppearance::AbilityAppearance(TextureManager* textureManager, Map* map) {
    this->generator = RandGenerator();
    this->textureManager = textureManager;
    this->map = map;
}

void AbilityAppearance::createAbility(Vector2D XYAppear, std::vector<AbilityIcon*>& buffs) {
    double randomAbility = this->generator.getRandNumber();

    if (this->generator.getRandNumber() <= 0.3) {
        if (randomAbility <= 0.35) {
            buffs.push_back(new ShieldIcon(XYAppear, "shield_ability", this->textureManager, this->map));
        } else if (randomAbility <= 0.65) {
            buffs.push_back(new MissileIcon(XYAppear, "missile_ability", this->textureManager, this->map));
        } else {
            buffs.push_back(new AutoShootIcon(XYAppear, "autoshoot_ability", this->textureManager, this->map));
        }
    }
}