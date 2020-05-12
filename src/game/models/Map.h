#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "MapElement.h"
#include "../../providers/GameProvider.h"
#include "Position.h"
#include "Speed.h"
#include "Orientation.h"
#include "../graphics/GraphicsSpacecraft.h"
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

class Map {
    private:
    vector <Level *> levels_;
    //void clearMap();

    public:
    Map();
    Map(gameParams_t &gameSettings);
    void update(currentStep_t currentStep);
    void addLevel(Level *level);
    vector<Level *> getLevels();
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
    // void createBackground(stageSource_t backgroundSource);
    void addStep(Step *step);
    vector<Step *> getSteps();
    void update(currentStep_t currentStep);
};

class Step: public Stage {
    private:
    unordered_map<IdElement, MapElement*> mapElements_;
    IdElement lastId_ = 0;

    public:
    Step();
    Step(stepParams_t params);
    //~Step();

    void update();
    // int move_in_direction(string movement_instruction,int id);
    // void createPlayer();
    // void createEnemy();
    // //void createBackground(level_t level);
    // void killMapElement(IdElement id);
};

#endif