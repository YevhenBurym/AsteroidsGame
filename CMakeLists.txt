cmake_minimum_required(VERSION 3.16)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Asteroids main.cpp
        Map/Map.cpp
        GameObject/GameObject.cpp
        AsteroidManager/AsteroidsManager.cpp
        Game/Game.cpp
        Window.cpp
        Sprite/Sprite.cpp
        InputComponent/InputComponent.cpp
        Collisions/Collisions.cpp
        GameObject/SpaceShip.cpp
        GameObject/Asteroid.cpp
        Vector2D/Vector2D.cpp
        SpriteManager/SpriteManager.cpp)

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
