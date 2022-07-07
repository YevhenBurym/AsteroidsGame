cmake_minimum_required(VERSION 3.16)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Asteroids main.cpp
        Map.cpp
        Map.h
        MoveableUnit.cpp
        MoveableUnit.h
        UnitManager.cpp
        UnitManager.h
        GameManager.cpp GameManager.h
        AsteroidsGame.h AsteroidsGame.cpp
        GameWindow.h GameWindow.cpp
        Sprite.h Sprite.cpp
        InputHandler.h InputHandler.cpp)

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
