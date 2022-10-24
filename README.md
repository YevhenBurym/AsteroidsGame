# Simple Asteroids
This project is a simple implementation of the Asteroids game. 
The project used the SDL library for graphics, keyboard and mouse polling.
## What has been implemented:
- game menu (main menu, pause menu, game over menu).
- counting downed asteroids and displaying it on the screen.
- centering the game relative to the player.
- two types of asteroids (small and big, which is divided into two small ones).
- three types of abilities (shield, homing missile, automatic shooting).
- run through the console with different game parameters:
-window [weight]х[height], -map [weight]х[height], -num_asteroids [amount], -num_ammo [amount].
## Used
- Cpp
- [SDL](https://github.com/libsdl-org/SDL)
- [SDL_image](https://github.com/libsdl-org/SDL_image)
- [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
## How to run this project
 - clone branch `main` with `https://github.com/YevhenBurym/AsteroidsGame.git` or fork it and then clone it from your forked repo.
 - The project can be built using a makefile in the project's root directory. All dll libraries that are needed to run are also in the root directory.
 - You can also run the compiled game with default parameters through the executable file `Asteroids.exe` in the root directory of the project.
 If run through the console, you can specify the initial parameters (for example: `Asteroids.exe -map 500x500` 
 or `Asteroids.exe -window 800x600 -num_asteroids 20`).
