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
    //Game(int wScreen, int hScreen);
    // no function calls are available here, this function should only return width, height and fullscreen values
    virtual void preInit(int& width, int& height, bool& fullscreen) = 0;

    // return : true - ok, false - failed, application will exit
    virtual bool init() = 0;

    virtual void close() = 0;

    // return value: if true will exit the application
    virtual bool tick() = 0;

    // param: xrel, yrel: The relative motion in the X/Y direction
    // param: x, y : coordinate, relative to window
    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

    virtual void onMouseButtonClick(GameMouseButton button, bool isReleased) = 0;

    virtual void onKeyPressed(GameKey k) = 0;

    virtual void onKeyReleased(GameKey k) = 0;

    virtual const char* getTitle() = 0;

    ~Game() {};
};