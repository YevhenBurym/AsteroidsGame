//
// Created by Евгений on 21.10.2022.
//

#pragma once

#include "../TextureManager/TextureManager.h"
#include "../Vector2D/Vector2D.h"

class MessageString {
private:
    TextureManager* textureManager;
    std::string textureID;
    int wSprite, hSprite;
    Vector2D xy;
public:
    MessageString(std::string fontID, std::string text, std::string textureID, TextureManager* textureManager);
    void setXY(Vector2D newXY);
    Vector2D getXY() const;
    void render();
};