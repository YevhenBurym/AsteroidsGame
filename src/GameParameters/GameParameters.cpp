//
// Created by Евгений on 05.10.2022.
//

#include "GameParameters.h"


GameParameters::GameParameters(int wScreen, int hScreen, bool isFullscreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit, double abilityProrability) {
    if (wScreen < 640) {
        wScreen = 640;
    }
    if (hScreen < 480) {
        hScreen = 480;
    }
    if (wMap < wScreen) {
        wMap = wScreen;
    }
    if (hMap < hScreen) {
        hMap = hScreen;
    }
    this->wScreen = wScreen;
    this->hScreen = hScreen;
    this->hMap = hMap;
    this->wMap = wMap;
    this->asteroidsLimit = asteroidsLimit;
    this->ammoLimit = ammoLimit;
    this->isFullScreen = isFullscreen;
}

int GameParameters::getHScreen() const {
    return this->hScreen;
}

int GameParameters::getWScreen() const {
    return this->wScreen;
}

int GameParameters::getHMap() const {
    return this->hMap;
}

int GameParameters::getWMap() const {
    return this->wMap;
}

int GameParameters::getAsteroidsLimit() const {
    return this->asteroidsLimit;
}

int GameParameters::getAmmoLimit() const {
    return this->ammoLimit;
}

bool GameParameters::getIsFullScreen() const {
    return this->isFullScreen;
}
