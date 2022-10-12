cmake_minimum_required(VERSION 3.16)
project(Asteroids)

set(CMAKE_CXX_STANDARD 11)

add_executable(Asteroids main.cpp
        src/Map/Map.cpp
        src/ObjectManager/ObjectManager.cpp
        src/Game/Game.cpp
        src/GameWindow/GameWindow.cpp
        src/InputHandler/InputHandler.cpp
        src/Collisions/Collisions.cpp
        src/GameObject/SpaceShip/SpaceShip.cpp
        src/GameObject/SmallAsteroid/SmallAsteroid.cpp
        src/Vector2D/Vector2D.cpp
        src/TextureManager/TextureManager.cpp
        src/GameObject/GameObject.cpp
        src/GameObject/Button/Button.cpp
        src/StateMachine/StateMachine.cpp
        src/GameStates/PlayState/PlayState.cpp
        src/GameStates/PauseState/PauseState.cpp
        src/GameStates/MenuState/MenuState.cpp
        src/GameStates/GameOverState/GameOverState.cpp
        src/GameObject/GameOverMessage/GameOverMessage.cpp
        src/GameParameters/GameParameters.cpp
        src/GameObject/Bullet/Bullet.cpp
        src/GameObject/Reticle/Reticle.cpp
        src/GameObject/BigAsteroid/BigAsteroid.cpp
        src/GameObject/AbilityObjects/ShieldObject/ShieldObject.cpp
        src/GameObject/AbilityObjects/MissileObject/MissileObject.cpp
        src/GameObject/AbilityObjects/AutoShootObject/AutoShootObject.cpp
        src/RandomGenerator/RandomGenerator.cpp
        src/AbilityAppearance/AbilityAppearance.cpp)


include_directories(${CMAKE_SOURCE_DIR}/SDL2/include/SDl2)
include_directories(${CMAKE_SOURCE_DIR}/SDL2/bin)
include_directories(${CMAKE_SOURCE_DIR}/SDL2/lib)

target_link_libraries(Asteroids
        -L${CMAKE_SOURCE_DIR}/SDL2/lib
        -lmingw32
        -lSDL2main
        -lSDL2
        -lSDL2_image)