#pragma once

#include <vector>
#include <cmath>
#include "../Vector2D/Vector2D.h"
#include "../TextureManager/TextureManager.h"

class GameObject {
protected:
    Vector2D coord;
    std::string textureID;
    int wSprite, hSprite;
    TextureManager* textureManager;
public:
    GameObject(Vector2D coord, std::string& textureID, TextureManager* textureManager);
    virtual ~GameObject() = default;
    virtual void setXY(Vector2D newXY);
    virtual Vector2D getXY() const;
    virtual void render();
    virtual void update() = 0;
};