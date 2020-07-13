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
    void updateState(currentStep_t actualStep);
    void updateGraphics();
    void clearScene();
    void sendStartStage(level_t oneLevel);
    void sendStageCleared(level_t oneLevel);
    void sendBackground(size_t numberLevel, size_t numberStage);

    public:
    Game(Server *server);
    ~Game();

    void run();
    void movePlayer(Id idUser, orientation_t orientation);
    void sendEvent(Event *event);
};

#endif