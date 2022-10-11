//
// Created by Евгений on 06.10.2022.
//

#pragma once

#include "../GameObject.h"

class Reticle : public GameObject {
public:
    Reticle(std::string textureID, TextureManager* textureManager);
    void render() override;
};
