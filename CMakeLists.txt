cmake_minimum_required(VERSION 3.16)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Asteroids main.cpp
        src/Map/Map.cpp
        src/GameObject/GameObject.cpp
        src/ObjectManager/ObjectManager.cpp
        src/Game/Game.cpp
        src/GameWindow/GameWindow.cpp
        src/InputComponent/InputComponent.cpp
        src/Collisions/Collisions.cpp
        src/GameObject/SpaceShip.cpp
        src/GameObject/Asteroid.cpp
        src/Vector2D/Vector2D.cpp
        src/TextureManager/TextureManager.cpp)


include_directories(${CMAKE_SOURCE_DIR}/SDL2/include/SDl2)
include_directories(${CMAKE_SOURCE_DIR}/SDL2/bin)
include_directories(${CMAKE_SOURCE_DIR}/SDL2/lib)

target_link_libraries(Asteroids
        -L${CMAKE_SOURCE_DIR}/SDL2/lib
        -lmingw32
        -lSDL2main
        -lSDL2
        -lSDL2_image)