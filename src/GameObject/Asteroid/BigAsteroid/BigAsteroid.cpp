//
// Created by Евгений on 06.10.2022.
//

#include "BigAsteroid.h"

BigAsteroid::BigAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID, TextureManager *textureManager,
                         Map *map) : Asteroid(coord, Vxy, textureID, textureManager, map) {
    this->mass = 2;
}

void BigAsteroid::divide(std::vector<Asteroid *> &objects) {
    Vector2D xy1;
    Vector2D xy2;
    xy1.setX(this->xy.getX() + this->radius);
    xy1.setY(this->xy.getY() + this->radius);
    xy2.setX(this->xy.getX() - this->radius);
    xy2.setY(this->xy.getY() - this->radius);

    auto smallAsteroid1 = new SmallAsteroid(xy1, {this->Vxy.getX(),-this->Vxy.getX()}, "small_asteroid", this->textureManager, this->map);
    auto smallAsteroid2 = new SmallAsteroid(xy2, {-this->Vxy.getX(),this->Vxy.getX()}, "small_asteroid", this->textureManager, this->map);
    objects.push_back(smallAsteroid1);
    objects.push_back(smallAsteroid2);
}
