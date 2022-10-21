//
// Created by Евгений on 21.10.2022.
//

#pragma once

#include "../MessageString/MessageString.h"

class ResultMessage {
private:
    MessageString* title;
    MessageString* smallAsteroidsTitle;
    MessageString* bigAsteroidsTitle;
    MessageString* bigAsteroidsAmount;
    MessageString* smallAsteroidsAmount;
    TextureManager* textureManager;
    int bigAmount;
    int smallAmount;
public:
    explicit ResultMessage(TextureManager* textureManager);
    void render();
    void setBigAsteroidsAmount(int amount);
    void setSmallAsteroidsAmount(int amount);
    ~ResultMessage();
};

