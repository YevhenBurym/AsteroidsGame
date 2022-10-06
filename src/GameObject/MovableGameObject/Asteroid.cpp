//
// Created by Евгений on 16.07.2022.
//

#include "Asteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
    this->mass = 1;
}

BigAsteroid::BigAsteroid(Vector2D coord, int velocity, int theta, std::string textureID, TextureManager* textureManager, Map* map) : MovableGameObject(coord, velocity, theta, textureID, textureManager, map) {
    this->mass = 2;
}

void BigAsteroid::divide(std::vector<MovableGameObject*>& objects) {
    Vector2D xy1;
    Vector2D xy2;
    xy1.setX(this->coord.getX() + this->xOf + this->radius);
    xy1.setY(this->coord.getY() + this->yOf + this->radius);
    xy2.setX(this->coord.getX() + this->xOf - this->radius);
    xy2.setY(this->coord.getY() + this->yOf - this->radius);

    objects.push_back(new SmallAsteroid(xy1, this->V.v, this->V.theta - 45, "small_asteroid", this->textureManager, this->map));
    objects.push_back(new SmallAsteroid(xy2, this->V.v, this->V.theta + 45, "small_asteroid", this->textureManager, this->map));
}