#pragma once


#include <vector>
#include <cmath>
#include "../Vector2D/Vector2D.h"
#include "../TextureManager/TextureManager.h"

#define RAD 3.14/180

class GameObject {
protected:
    Vector2D coord;
    std::string textureID;
    int wSprite, hSprite;
    TextureManager* textureManager;
public:
    GameObject(Vector2D coord, std::string textureID, TextureManager* textureManager);
    virtual ~GameObject() = default;
    virtual void setX(double x);
    virtual void setY(double y);
    virtual double getX() const;
    virtual double getY() const;
    virtual void render() const;
};