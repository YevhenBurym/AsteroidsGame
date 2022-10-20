#include "src/Game/Game.h"
#include <sstream>

int main(int argc, char* argv[]) {
	int wScreen = 800;
	int hScreen = 600;
	int wMap = 1000;
	int hMap = 1000;
	int asteroidsLimit = 30;
	int ammoLimit = 5;

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
			if (asteroidsLimit == 0) asteroidsLimit = 25;
		}
		if (str == "-num_ammo") {
			std::stringstream value(str1);
			ammoLimit = atol(str1.c_str());
			if (ammoLimit == 0) ammoLimit = 5;
		}
	}
    Game* game = new Game(new GameParameters(wScreen, hScreen, false, wMap, hMap, asteroidsLimit, ammoLimit));
	game->run();

	return 0;
}

