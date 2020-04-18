#ifndef _GAME_H_
#define _GAME_H_

#include "../providers/GameProvider.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../services/Logger.h"

//Consts
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Game {

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    void processEvent();
    void updateState();
    void updateGraphics();

    void initializeGraphics();

    public:
    Game();
    ~Game();

    void loop();
};

#endif