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

#include "../../common/models/events/EventInitStage.h"
#include "../../common/models/events/Event.h"

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla
class MapElement;
class Step;
class Stage;
class Level;

class Map {
    private:
    vector <Level *> levels_;
    //void clearMap();
    //MapElement *player;
    unordered_map<string, MapElement*> players;

    public:    
    Map();
    Map(gameParams_t &gameSettings);
    void update(currentStep_t currentStep);
    void addLevel(Level *level);
    vector<Level *> getLevels();
    void setStageSource(size_t numberLevel, size_t numberStage);
    bool endStep(currentStep_t currentStep);
    void createPlayers(gameParams_t &gameSettings);
    void initializePositionPlayers(gameParams_t &gameSettings);
    void movePlayer(string namePlayer, orientation_t orientation);
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
    void update(currentStep_t currentStep);
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
    // MapElement* createMapElement();
    void addStep(Step *step);
    vector<Step *> getSteps();
    void update(currentStep_t currentStep);
    bool endStep(size_t numberStep);
};

class Step: public Stage {
    private:
    unordered_map<IdElement, MapElement*> mapElements_;
    IdElement lastId_ = 0;
    position_t getPosition(int sizeMapElement_x, int sizeMapElement_y);

    public:
    Step();
    Step(stepParams_t params);
    //~Step();


    void update();
    bool endStep();
    // int move_in_direction(string movement_instruction,int id);
    // void createEnemy();    
    // void killMapElement(IdElement id);
};

#endif