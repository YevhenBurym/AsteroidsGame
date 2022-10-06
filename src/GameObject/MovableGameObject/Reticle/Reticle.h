//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../MovableGameObject.h"

class Reticle : public MovableGameObject {
public:
    Reticle(std::string textureID, TextureManager* textureManager, Map* map);
    void render() const override;
};
