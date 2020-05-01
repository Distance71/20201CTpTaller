#ifndef _GAME_H_
#define _GAME_H_

#include <ctime>
#include "../../providers/GameProvider.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../services/Logger.h"
#include "../../services/SpriteGenerator.h"
#include "Map.h"


// Maneja la secuencia logica del juego

class Game {

    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    Map *map_;

    void processEvent();
    void updateState();
    void updateGraphics();

    void initializeGraphics();

    public:
    Game();
    ~Game();

    void run();
    bool login();
};

#endif