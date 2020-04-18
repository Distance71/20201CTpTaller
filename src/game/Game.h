#ifndef _GAME_H_
#define _GAME_H_

#include "../providers/GameProvider.h"
#include "SDL.h"
#include "../services/Logger.h"

//Consts
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Game {

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer_ = nullptr;

    void initializeGraphics();
    void handleInput();
    void generateGraphics();

    public:
    Game();
    ~Game();

    void loop();

};

#endif