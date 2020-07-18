#ifndef _GAME_H_
#define _GAME_H_

#include <ctime>
#include "../../common/providers/GameProvider.h"
#include "../../common/services/Logger.h"
#include "Map.h"
#include <chrono>
#include <string>

#include "../../common/models/events/Event.h"
#include "MapElement.h"
#include "../Server.h"

// Maneja la secuencia logica del juego
class Server;
class Map;
class Level;
class Stage;
class Step;

class Game {

    private:
    Server *serverOwn_;
    Map *map_;

    void initializeGameParams();
    void runLevel(currentStep_t actualStep, Level *level);
    void runStage(currentStep_t actualStep, Stage *stage);
    void runStep(currentStep_t actualStep);

    void processEvent();
    void initializeStep(currentStep_t actualStep);
    void updateState(currentStep_t actualStep);
    void updateGraphics();
    void clearScene();
    void sendStartStage(level_t oneLevel);
    void sendStageCleared(level_t oneLevel);
    void sendBackground(level_t oneLevel);

    public:
    Game(Server *server);
    ~Game();

    void run();
    void movePlayer(string user, orientation_t orientation);
    void sendEvent(Event *event);

    void informDisconnection(string user); 
    void informConnection(string user); 
};

#endif