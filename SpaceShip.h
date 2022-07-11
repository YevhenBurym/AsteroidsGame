//
// Created by Евгений on 11.07.2022.
//

#pragma once
#include "InputComponent.h"

class SpaceShip {
public:
    void update();
private:
    int v;
    int x,y;
    PlayerInputComponent* input;
};


