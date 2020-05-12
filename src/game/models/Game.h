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

//para probar
#include "MapElement.h"

// Maneja la secuencia logica del juego

class Game {

    private:
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    Map *map_;

    void initializeGameParams();
    void runLevel(currentStep_t actualStep, Level *level);
    void runStage(currentStep_t actualStep, Stage *stage);
    void runStep(currentStep_t actualStep);

    void processEvent();
    void updateState(currentStep_t actualStep);
    void updateGraphics();
    void clearScene();
    void initializeGraphics();

    public:
    Game();
    ~Game();

    void run();
    bool login();
    //GraphicsScenario play_level(int level);
};

#endif