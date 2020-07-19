#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include "MapElement.h"
#include "../../common/providers/GameProvider.h"
#include "../../common/models/Position.h"
#include "../../common/models/Orientation.h"
#include "MovementHandler.h"
#include "PlayerController.h"
#include "../../common/types.h"

#include "../../common/models/events/Event.h"
#include "Game.h"

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla
class Game;
class MapElement;
class Step;
class Stage;
class Level;

class Map {
    private:
    vector <Level *> levels_;
    unordered_map<string, MapElement*> players;
    void updatePlayers(Game *game);
    size_t loggedPlayers_ = 0;

    elementType_t getPlayerType();
    position_t getInitialPosition();

    public:    
    Map();
    Map(gameParams_t &gameSettings);
    void update(currentStep_t currentStep, Game *game);
    void addLevel(Level *level);
    vector<Level *> getLevels();
    bool endStep(currentStep_t currentStep);
    void initializePositionPlayers(gameParams_t &gameSettings);
    void movePlayer(string user, orientation_t orientation);

    void initializeStep(currentStep_t currentStep, Game *game);

    void informDisconnection(string user); 
    void informConnection(string user); 
};

class Level: public Map {
    private:
    vector<Stage *> stages_;
    //void clearStage();

    public:
    Level();
    Level(levelParams_t &params);
    void addStage(Stage *stage);
    vector<Stage *> getStages();
    void update(currentStep_t currentStep, Game *game);
    void initializeStep(currentStep_t currentStep, Game *game);
    bool endStep(size_t numberStage, size_t numberStep);
};

class Stage: public Level {
    private:
    vector<Step *> steps_;
    //IdElement lastId_ = 0;
    void clearMap();

    public:
    
    Stage();
    Stage(stageParams_t &params);
    void addStep(Step *step);
    vector<Step *> getSteps();
    void update(currentStep_t currentStep, Game *game);
    bool endStep(size_t numberStep);
    void initializeStep(currentStep_t currentStep, Game *game);
};

class Step: public Stage {
    private:
    unordered_map<Id, MapElement*> mapElements_;
    Id lastId_ = 0;
    position_t getPosition(int sizeMapElement_x, int sizeMapElement_y);

    public:
    Step();
    Step(stepParams_t params);


    void update(Game *game);
    void initializeStep(Game *game);
    bool endStep();
};

#endif