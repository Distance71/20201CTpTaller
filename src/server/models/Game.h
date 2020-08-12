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
    void runStage(currentStep_t actualStep, Stage *stage, bool isFinalStage);
    void runStep(currentStep_t actualStep);

    void processEvent();
    void initializeStep(currentStep_t actualStep);
    void updateState(currentStep_t actualStep);
    void updateGraphics();
    void clearScene();
    void sendStartStage(stage_t stage);
    void sendStageCleared(stage_t stage);
    void sendGameOver();

    void runFinal();
    public:
    Game(Server *server);
    ~Game();

    void run();
    void movePlayer(string user, orientation_t orientation);
    void changeGameModePlayer(string user);
    void shootPlayer(string user);
    void sendEvent(Event *event);
    void sendEventToUser(string username, Event* event);
    Map* getMap();

    void informDisconnection(string user); 
    void informConnection(string user); 
};

#endif