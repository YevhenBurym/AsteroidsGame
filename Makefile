all: Asteroids clean
Asteroids: main ObjectManager Collisions Button StateMachine PlayState PauseState MenuState GameOverState GameOverMessage ShieldIcon \
           MissileIcon AutoShootIcon AbilityAppearance AbilityIcon ResultMessage MessageString Game SpaceShip SmallAsteroid BigAsteroid \
           Asteroid Bullet Reticle Missile GameObject Map GameWindow TextureManager InputHandler RandomGenerator GameParameters Vector2D
	g++ -o Asteroids.exe *.o -ISDL2/include/SDl2 -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
main:
	g++ -c -std=c++11 -ISDL2/include/SDl2 main.cpp -o main.o
ObjectManager:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/ObjectManager/ObjectManager.cpp -o ObjectManager.o
Collisions:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/Collisions/Collisions.cpp -o Collisions.o
Button:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Button/Button.cpp -o Button.o
StateMachine:
	g++ -c -std=c++11 src/StateMachine/StateMachine.cpp -o StateMachine.o
PlayState:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameStates/PlayState/PlayState.cpp -o PlayState.o
PauseState:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameStates/PauseState/PauseState.cpp -o PauseState.o
MenuState:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameStates/MenuState/MenuState.cpp -o MenuState.o
GameOverState:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameStates/GameOverState/GameOverState.cpp -o GameOverState.o
GameOverMessage:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/GameOverMessage/GameOverMessage.cpp -o GameOverMessage.o
ShieldIcon:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/AbilityIcon/ShieldIcon/ShieldIcon.cpp -o ShieldIcon.o
MissileIcon:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/AbilityIcon/MissileIcon/MissileIcon.cpp -o MissileIcon.o
AutoShootIcon:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/AbilityIcon/AutoShootIcon/AutoShootIcon.cpp -o AutoShootIcon.o
AbilityAppearance:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/AbilityAppearance/AbilityAppearance.cpp -o AbilityAppearance.o
AbilityIcon:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/AbilityIcon/AbilityIcon.cpp -o AbilityIcon.o
ResultMessage:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/ResultMessage/ResultMessage.cpp -o ResultMessage.o
MessageString:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/MessageString/MessageString.cpp -o MessageString.o
Game:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/Game/Game.cpp -o Game.o
SpaceShip:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/SpaceShip/SpaceShip.cpp -o SpaceShip.o
SmallAsteroid:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Asteroid/SmallAsteroid/SmallAsteroid.cpp -o SmallAsteroid.o
BigAsteroid:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Asteroid/BigAsteroid/BigAsteroid.cpp -o BigAsteroid.o
Asteroid:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Asteroid/Asteroid.cpp -o Asteroid.o
Bullet:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Bullet/Bullet.cpp -o Bullet.o
Reticle:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Reticle/Reticle.cpp -o Reticle.o
Missile:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/Missile/Missile.cpp -o Missile.o
GameObject:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameObject/GameObject.cpp -o GameObject.o
Map:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/Map/Map.cpp -o Map.o
GameWindow:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/GameWindow/GameWindow.cpp -o GameWindow.o
TextureManager:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/TextureManager/TextureManager.cpp -o TextureManager.o
InputHandler:
	g++ -c -std=c++11 -ISDL2/include/SDl2 src/InputHandler/InputHandler.cpp -o InputHandler.o
RandomGenerator:
	g++ -c -std=c++11 src/RandomGenerator/RandomGenerator.cpp -o RandomGenerator.o
GameParameters:
	g++ -c -std=c++11 src/GameParameters/GameParameters.cpp -o GameParameters.o
Vector2D:
	g++ -c -std=c++11 src/Vector2D/Vector2D.cpp -o Vector2D.o
clean:
	rm  *.o

