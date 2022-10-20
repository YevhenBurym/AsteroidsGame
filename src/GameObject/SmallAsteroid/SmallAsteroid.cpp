//
// Created by Евгений on 16.07.2022.
//

#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(Vector2D coord, Vector2D Vxy, std::string textureID,
                             TextureManager *textureManager, Map *map) : Asteroid(coord, Vxy, textureID,
                                                                                    textureManager, map)
                                                                                    {}

