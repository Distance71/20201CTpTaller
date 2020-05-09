#ifndef _GAME_H_
#define _GAME_H_

#include <ctime>
#include "../../providers/GameProvider.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../services/Logger.h"
#include "Sprite.h"
#include "Map.h"
#include "../graphics/GraphicsScenario.h"
#include <chrono>
#include <string>

#define LEVEL_ONE_N_STAGES 5
#define LEVEL_TWO_N_STAGES 4

// Maneja la secuencia logica del juego

class Game {

    private:
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    Map * map_;

    void processEvent();
    void updateState();
    void updateGraphics();
    void clearScene();
    void initializeGraphics();
    void initializeLevelOne();

    public:
    Game();
    ~Game();

    void run();
    bool login();
    //GraphicsScenario play_level(int level);
};

#endif