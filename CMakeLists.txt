cmake_minimum_required(VERSION 3.16)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Asteroids main.cpp
        Map.cpp
        Map.h
        GameObject.cpp
        GameObject.h
        AsteroidsManager.cpp
        AsteroidsManager.h
        Game.h Game.cpp
        Window.h Window.cpp
        Sprite.h Sprite.cpp
        InputComponent.h InputComponent.cpp
        Collisions.h Collisions.cpp
        SpaceShip.h SpaceShip.cpp
        Asteroid.h Asteroid.cpp
        Vector2D.h Vector2D.cpp)

include_directories(D:/2.SelfStudy/AsteroidsGame)

include_directories(C:/mingwLibs/SDL2/include/SDL2)
include_directories(C:/mingwLibs/SDL_Image/include/SDL2)
include_directories(C:/mingwLibs/SDL_Image/bin)

target_link_libraries(Asteroids
        -LC:/mingwLibs/SDL2/lib
        -LC:/mingwLibs/SDL_Image/lib
        -lmingw32
        -lSDL2main
        -lSDL2
        -lSDL2_image)
