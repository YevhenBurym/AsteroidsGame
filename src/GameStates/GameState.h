//
// Created by Евгений on 20.07.2022.
//

#pragma once

#include<string>
#include <iostream>

class GameState {
public:
    virtual ~GameState() = default;

    virtual void update() = 0;

    virtual void render() = 0;

    virtual bool onEnter() = 0;

    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;
};
