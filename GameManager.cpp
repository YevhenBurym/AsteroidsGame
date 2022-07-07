//
// Created by Евгений on 03.07.2022.
//

#include "GameManager.h"
#include "GameWindow.h"

//static SDL_Window* window = nullptr;
//static SDL_Renderer* renderer = nullptr;
//static bool isCursorShown = true;

//SDL_Texture* createTexture(const char* path) {
//    SDL_Texture* newTexture = nullptr;
//
//    newTexture = IMG_LoadTexture(renderer, path);
//
//    if( newTexture == nullptr ) {
//        std::cout << "Failed to load texture image!" << std::endl;
//    }
//    return newTexture;
//}
//
//void drawTexture(SDL_Texture* texture, int x, int y) {
//    SDL_Rect drawParams{x, y,0,0};
//    getTextureSize(texture,drawParams.w,drawParams.h);
//
//    SDL_RenderCopy( renderer, texture, nullptr, &drawParams );
//}
//
//void drawTexture(SDL_Texture* texture, int x, int y, double angle) {
//    SDL_Rect drawParams{x, y,0,0};
//    getTextureSize(texture,drawParams.w,drawParams.h);
//
//    SDL_RenderCopyEx(renderer, texture, nullptr, &drawParams, angle,nullptr,SDL_FLIP_NONE);
//}
//
//void destroyTexture(SDL_Texture* texture) {
//    //Free loaded image
//    SDL_DestroyTexture( texture );
//    texture = nullptr;
//}
//
//void getTextureSize(SDL_Texture* texture, int& w, int& h) {
//    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
//}
//
//void getSize(int& wScreen, int& hScreen) {
//    SDL_GetWindowSize(window, &wScreen, &hScreen);
//}
//
//uint32_t getTickCounting() {
//    return SDL_GetTicks();
//}
//
//void showCursor(bool isShow) {
//    isCursorShown = isShow;
//}



