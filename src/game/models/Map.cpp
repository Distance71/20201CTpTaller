#include "Map.h"

Map::Map(){
    //Necesitaba crearlo para compilar   
}

Map::Map(gameParams_t &gameSettings){
    size_t nLevels = 1; //gameSettings.levelParams.size();

    // for(size_t i = 0; i < nLevels; i++){
    //     Level *newLevel = new Level(gameSettings.levelParams[i]);
    //     this->addLevel(newLevel);
    // }
}

Level::Level(){
    //Necesitaba crearlo para compilar
}

Level::Level(levelParams_t &params){
    size_t nStages = 1; //params.stagesParams.size();

    // for(size_t i = 0; i < nStages; i++){
    //     //Stage *newStage = new Stage(params.stageParams[i]);
    //     //this->addStage(newStage);
    // }
}

Stage::Stage(){
    //Necesitaba crearlo para compilar
}

Stage::Stage(stageParams_t &params){
    size_t quantitySteps = 1; //params.stepsParams.size();
    
    for(size_t i = 0; i < quantitySteps; i++) {
        //Step *step = new Step(params.stepsParams[i]);
        //this->addStep(step);
    }
}

Step::Step(){
    //Necesitaba crearlo para compilar
}

Step::Step(stepParams_t params) {
    //Do something -> create enemies of different types, rocks, etc
}

void Map::addLevel(Level *level){
    if(!level){
        //Validate
    }
    levels_[levels_.size()] = level;
}

void Level::addStage(Stage *stage){
    if(!stage) {
        //Validate
    }

    stages_[stages_.size()] = stage;
}

void Stage::addStep(Step *step){
    if(!step) {
        //Validate
    }

    this->steps_[this->steps_.size()] = step;
}

vector<Level *> Map::getLevels(){
     return this->levels_;
}

vector<Stage *> Level::getStages(){
     return this->stages_;
}

vector<Step *> Stage::getSteps(){
     return this->steps_;
}

// // int Step::move_in_direction(string movement_instruction, int id){
// //     // si devuelve 0 todo ok, ante cualquier problema que devuelva 1 
// //     //para poder registrarlo en el logger
// //     return 0;
// // }

void Map::update(currentStep_t currentStep){
    //size_t actualLevel = currentStep.level;
        
    //levels_[actualLevel]->update();
}

void Level::update(currentStep_t currentStep){
    size_t actualStage = currentStep.stage;
        
    //stages_[actualStage]->update();
}

void Stage::update(currentStep_t currentStep){
    size_t actualStep = currentStep.step;
    
    //steps_[actualStep]->update();
}

void Step::update(){
    for(auto mapElement : mapElements_) {
        mapElement.second->update();
    }
}

// void Step::createBackground(stageSource_t backgroundSource){
//     MapElement* background = new MapElement(BACKGROUND);
//     lastId_++;
//     stageData = GameProvider::getConfig()->getStageData(LEVEL_ONE);

//     auto *graphics = new GraphicsScenario(backgroundSource);
    
//     background->addAction("Graphics", graphics);

//     mapElements_[lastId_] = background;
// }

// // void Step::createPlayer(){
// //     MapElement* player = new MapElement(PLAYER);
// //     lastId_++;

// //     Position *initialPosition = new Position(); //Should have a initial player positionHandler
// //     Speed *speed = new Speed(); //This should be taken from config
// //     Orientation *initialOrientation = new Orientation(); //Should be Front
// //     auto *graphics = new GraphicsSpacecraft();
// //     auto *movementHandler = new PlayerController(lastId_);

// //     player->addState("Position", initialPosition);
// //     player->addState("Speed", speed);
// //     player->addState("Orientation", initialOrientation);
// //     player->addAction("Graphics", graphics);
// //     player->addAction("MovementHandler", movementHandler);

// //     mapElements_[lastId_] = player;
// // }

// // void Step::createEnemy(){
// //     MapElement* enemy = new MapElement(ENEMY);
// //     lastId_++;

// //     Position *initialPosition = new Position(); //Should have a initial player positionHandler() or class if grows
// //     Speed *speed = new Speed(); //This should be taken from config
// //     Orientation *initialOrientation = new Orientation(); //Should be Front
// //     auto *graphics = new GraphicsSpacecraft();
// //     auto *movementHandler = new PlayerController(lastId_);

// //     enemy->addState("Position", initialPosition);
// //     enemy->addState("Speed", speed);
// //     enemy->addState("Orientation", initialOrientation);
// //     enemy->addAction("Graphics", graphics);
// //     enemy->addAction("MovementHandler", movementHandler);

// //     mapElements_[lastId_] = enemy;
// // }

// // void Step::killMapElement(IdElement id){
// //     if(!mapElements_[id] || id > lastId_){
// //         Logger::getInstance()->log(ERROR, "Se intentó eliminar un elemento del mapa invalido");
// //         return;
// //     }
// //     delete mapElements_[id];
// //     mapElements_[id] = NULL;
// // }

// /*MapElement* Step::createMapElement(){
//     auto *mapElement = new MapElement();
//     IdElement lastId = lastId_;

//     mapElements_[++lastId_] = mapElement;
//     return mapElement;
// }*/

// // void Step::clearMap() {
// //     //mapElements_.clear();
// //     Logger::getInstance()->log(DEBUG, "Se vaciaron los elementos del mapa");
// // }