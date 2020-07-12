#ifndef _GAME_H_
#define _GAME_H_

#include <ctime>
#include "../../common/providers/GameProvider.h"
#include "../../common/services/Logger.h"
#include "Map.h"
#include <chrono>
#include <string>

#include "../../common/models/events/EventInitStage.h"
#include "../../common/models/events/Event.h"
#include "MapElement.h"
#include "../Server.h"

// Maneja la secuencia logica del juego
class Server;

class Game {

    private:
        Server *serverOwn_;
    Map *map_;

    void initializeGameParams();
    void runLevel(currentStep_t actualStep, Level *level);
    void runStage(currentStep_t actualStep, Stage *stage);
    void runStep(currentStep_t actualStep);

    void processEvent();
    void updateState(currentStep_t actualStep);
    void updateGraphics();
    void clearScene();
    void sendStartStage(level_t oneLevel);
    void viewStageCleared(level_t oneLevel);

    public:
    Game(Server *server);
    ~Game();

    void run();
    void movePlayer(string nameUser, orientation_t orientation);
};

#endif