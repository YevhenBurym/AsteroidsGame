//
// Created by Евгений on 20.10.2022.
//

#include "AbilityIcon.h"

AbilityIcon::AbilityIcon(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager, Map* map)
        : GameObject(coord, Vxy, textureID, textureManager ) {
    double d;
    this->hSprite = 0;
    this->wSprite = 0;
    this->textureManager = textureManager;
    this->textureID = textureID;
    textureManager->getTextureSize(textureID,this->wSprite,this->hSprite);

    if (this->wSprite % this->hSprite == this->wSprite) {
        d = this->hSprite - (this->hSprite % this->wSprite) / 2;
    } else {
        d = this->wSprite - (this->wSprite % this->hSprite) / 2;
    }
    this->radius = d / 2;
    this->xy = coord;
    this->Vxy = Vxy;
    this->mass = 1;
    this->xyOffset = {0,0};
    this->acceleration = {0,0};
    this->map = map;
    this->xyOffset = map->getXY();
    this->existingDuration = 5;
    this->isExist = true;
    this->startExistingTimer = std::chrono::high_resolution_clock::now();
}

void AbilityIcon::update() {
    this->xyOffset = this->map->getXY();
    GameObject::update();
    this->endExistingTimer = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = this->endExistingTimer - this->startExistingTimer;
    if (duration.count() >= this->existingDuration) {
        this->isExist = false;
    }
}

bool AbilityIcon::getIsExist() const {
    return this->isExist;
}
