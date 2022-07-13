#include "Game.h"
#include <sstream>

int main(int argc, char* argv[]) {
	//-window 800x600 - map 1000x1000 - num_asteroids 10 - num_ammo 3 - ability_probability 0.3
	int wScreen = 800;
	int hScreen = 600;
	int wMap = 500;
	int hMap = 500;
	int asteroidsLimit = 10;
	int ammoLimit = 5;
	double abilityProrability = 0.3;

	for (int i = 1; i < argc; ++i) {
		std::string str = argv[i-1];
		std::string str1 = argv[i];
		if (str == "-window") {
			std::stringstream value(str1);
			std::string wValue;
			std::string hValue;
			std::getline(value, wValue, 'x');
			std::getline(value, hValue, 'x');
			wScreen = atol(wValue.c_str());
			hScreen = atol(hValue.c_str());
			if (hScreen == 0 || wScreen == 0) {
				wScreen = 800;
				hScreen = 600;
			}
		}
		if (str == "-map") {
			std::stringstream value(str1);
			std::string wValue;
			std::string hValue;
			std::getline(value, wValue, 'x');
			std::getline(value, hValue, 'x');
			wMap = atol(wValue.c_str());
			hMap = atol(hValue.c_str());
			if (hMap == 0 || wMap == 0) {
				wMap = 1000;
				hMap = 1000;
			}
		}
		if (str == "-num_asteroids") {
			std::stringstream value(str1);
			asteroidsLimit = atol(str1.c_str());
			if (asteroidsLimit == 0) asteroidsLimit = 10;
		}
		if (str == "-num_ammo") {
			std::stringstream value(str1);
			ammoLimit = atol(str1.c_str());
			if (ammoLimit == 0) asteroidsLimit = 3;
		}
		if (str == "-ability_probability") {
			std::stringstream value(str1);
			abilityProrability = atof(str1.c_str());
			if (abilityProrability == 0) abilityProrability = 0.3;
		}

	}
    Game* game = new Game(wScreen, hScreen, wMap, hMap, asteroidsLimit, ammoLimit, abilityProrability);
    game->runGame();

	return 0;
}
