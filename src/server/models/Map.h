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
#include "MapElementBackground.h"

#include "../../common/services/RandomGenerate.h"
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
    
    //void updatePlayers(Game *game);
    size_t loggedPlayers_ = 0;

    elementType_t getPlayerType();
    position_t getInitialPosition();

    unordered_map<string, MapElement*> players;
    MapElement* finalBoss_;

    public:    
    Map();
    Map(gameParams_t &gameSettings);
    void update(currentStep_t currentStep, Game *game);
    void addLevel(Level *level);
    vector<Level *> getLevels();
    bool endStep(currentStep_t currentStep);
    void initializePositionPlayers(gameParams_t &gameSettings);
    void initializeFinalBoss(gameParams_t &gameSettings);
    void movePlayer(string user, orientation_t orientation);
    void shootPlayer(string user);

    void updateFinal(Game* game);

    MapElement* getRandomTarget(Game* game);
    void setTargetsForStep(currentStep_t actualStep, Game *game);
    void cleanStage();

    void initializeStep(currentStep_t currentStep, Game *game);

    void informDisconnection(string user); 
    void informConnection(string user); 
};

class Level: public Map {
    private:
    vector<Stage *> stages_;

    public:
    Level();
    Level(levelParams_t &params);
    void addStage(Stage *stage);
    vector<Stage *> getStages();
    void setTargetsForStep(currentStep_t actualStep, Game *game);
    void update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players);
    void updateFinal(Game *game, unordered_map<string, MapElement*> players, MapElement* finalBoss);
    void initializeStep(currentStep_t currentStep, Game *game);
    bool endStep(size_t numberStage, size_t numberStep);
};

class Stage: public Level {
    private:
    vector<Step *> steps_;
    vector<unordered_map<layer_t, MapElementBackground*>> stagesBackground_;
    void clearMap();
    void createBackground();

    MapElementBackground* buildStageBackgroundLayer(layer_t layer, stage_t stage, int speedX);
    
    public:
    
    Stage();
    Stage(stageParams_t &params);
    void addStep(Step *step);
    vector<Step *> getSteps();
    void setTargetsForStep(currentStep_t actualStep, Game *game);
    void update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players);
    void updateFinal(Game *game, unordered_map<string, MapElement*> players, MapElement* finalBoss, stage_t stage);
    bool endStep(size_t numberStep);
    void initializeStep(currentStep_t currentStep, Game *game);
    void updateBackground(Game *game, stage_t stage);
};

class Step: public Stage {
    private:
    unordered_map<Id, MapElement*> mapElements_;
    Id lastId_ = 0;
    position_t getPosition(int sizeMapElement_x, int sizeMapElement_y);

    public:
    Step();
    Step(stepParams_t params);

    void setTargetsForStep(Game *game);
    void update(Game *game);
    void initializeStep(Game *game);
    void shootEnemy();
    bool endStep();
};

#endif