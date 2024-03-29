//
// Created by Евгений on 05.10.2022.
//

#pragma once

class GameParameters {
private:
    int wScreen, hScreen;
    int hMap, wMap;
    int asteroidsLimit;
    int ammoLimit;
    bool isFullScreen;
public:
    GameParameters(int wScreen, int hScreen, bool isFullscreen, int wMap, int hMap, int asteroidsLimit, int ammoLimit);
    int getHScreen() const;
    int getWScreen() const;
    int getHMap() const;
    int getWMap() const;
    int getAsteroidsLimit() const;
    int getAmmoLimit() const;
    bool getIsFullScreen() const;
};

