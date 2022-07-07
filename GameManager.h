//
// Created by Евгений on 03.07.2022.
//
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


enum class GameKey {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    COUNT
};

enum class GameMouseButton {
    LEFT,
    MIDDLE,
    RIGHT,
    COUNT
};

class Game {
public:
    // return : true - ok, false - failed, application will exit
    virtual bool init() = 0;

    virtual void close() = 0;

    // return value: if true will exit the application
    virtual bool tick() = 0;

    ~Game() {};
};