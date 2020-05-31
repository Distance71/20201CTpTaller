#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include "MapElement.h"
#include "../../providers/GameProvider.h"
#include "Position.h"
#include "Speed.h"
#include "Orientation.h"
#include "../graphics/GraphicsScenario.h"
#include "MovementHandler.h"
#include "PlayerController.h"
#include "../types.h"


//Para probar
#include "Speed.h"
#include "Position.h"
#include "Sprite.h"
#include "../graphics/GraphicsMapElement.h"

// Es el contenedor principal del juego. Se va mostrando una parte de este en la pantalla
class MapElement;
class Step;
class Stage;
class Level;
class GraphicsScenario;

class Map {
    private:
    vector <Level *> levels_;  
    GraphicsScenario *escenario_;
    //void clearMap();
    MapElement *player;

    public:    
    Map();
    Map(gameParams_t &gameSettings);
    void update(currentStep_t currentStep);
    void addLevel(Level *level);
    vector<Level *> getLevels();
    void setStageSource(size_t numberLevel, size_t numberStage);
    GraphicsScenario* getCurrentScenario();
    bool endStep(currentStep_t currentStep);
    void createPlayer(gameParams_t &gameSettings);
    void initializePositionPlayer(gameParams_t &gameSettings);
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