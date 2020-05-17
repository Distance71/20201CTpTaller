#include "Map.h"
Map::Map(){
    //Necesitaba crearlo para compilar   
}

Map::Map(gameParams_t &gameSettings){
    size_t nLevels = gameSettings.levelParams.size();

    Logger::getInstance()->log(DEBUG, "Se crea entidad Map.");
    Logger::getInstance()->log(DEBUG, "Se procesa el Game Setting.");

    for(size_t i = 0; i < nLevels; i++){
        Level *newLevel = new Level(gameSettings.levelParams[i]);
        this->addLevel(newLevel);
    }
    createPlayer(gameSettings);
}

void Map::setStageSource(size_t numberLevel, size_t numberStage){
    stageSource_t background = GameProvider::getConfig()->getSourcesForStage(numberLevel,numberStage);
    this->escenario_= new GraphicsScenario(background);
}

GraphicsScenario *Map::getCurrentScenario(){
    return this->escenario_;
}

bool Map::endStep(currentStep_t currentStep){
    return this->levels_[currentStep.level]->endStep(currentStep.stage, currentStep.step);
}

Level::Level(){
    //Necesitaba crearlo para compilar
}

Level::Level(levelParams_t &params){
    
    size_t nStages = params.stagesParams.size();

    for(size_t i = 0; i < nStages; i++){
        Stage *newStage = new Stage(params.stagesParams[i]);
        this->addStage(newStage);
    }
}

bool Level::endStep(size_t numberStage, size_t numberStep){
    return this->stages_[numberStage]->endStep(numberStep);
}

Stage::Stage(){
    //Necesitaba crearlo para compilar
}

Stage::Stage(stageParams_t &params){
    size_t quantitySteps = params.stepsParams.size();
    
    for(size_t i = 0; i < quantitySteps; i++) {
        Step *step = new Step(params.stepsParams[i]);
        this->addStep(step);
    }
}

bool Stage::endStep(size_t numberStep){
    return this->steps_[numberStep]->endStep();
}

Step::Step(){
    //Necesitaba crearlo para compilar
}

Step::Step(stepParams_t params) {
    //Do something -> create enemies of different types, rocks, etc
    size_t nEnemies = params.enemies.size();
    
    for(size_t i = 0; i < nEnemies; i++){
        unsigned int nEnemiesIguales = params.enemies[i].quantity;
        string sprite = params.enemies[i].sprite;
        int size_x = params.enemies[i].size_x;
        int size_y = params.enemies[i].size_y;
        
        for(unsigned int j = 0; j < nEnemiesIguales; j++){
            //Las posiciones y demas son de prueba
            MapElement *newEnemy = new MapElement(ENEMY,i*100 + j*100,j*40,2,2,sprite, size_x, size_y);
            this->mapElements_[this->lastId_] = newEnemy;
            this->lastId_++;
        }
    }
}

bool Step::endStep(){
    // Igual a 1 porque solo quedaria un jugador -> habria que cambiarlo despues
    return (this->mapElements_.size() == 0);
}

void Map::addLevel(Level *level){
    if(!level){
        //Validate
    }
    
    this->levels_.push_back(level);
    //levels_[levels_.size()] = level;
}

void Level::addStage(Stage *stage){
    if(!stage) {
        //Validate
    }

    this->stages_.push_back(stage);
    //stages_[stages_.size()] = stage;
}

void Stage::addStep(Step *step){
    if(!step) {
        //Validate
    }

    this->steps_.push_back(step);
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
    size_t actualLevel = currentStep.level;
        
    this->player->update();
    levels_[actualLevel]->update(currentStep);
}

void Level::update(currentStep_t currentStep){
    size_t actualStage = currentStep.stage;
        
    stages_[actualStage]->update(currentStep);
}

void Stage::update(currentStep_t currentStep){
    size_t actualStep = currentStep.step;

    steps_[actualStep]->update();
}

void Step::update(){

    vector<IdElement> mapElementDead;

    for(auto mapElement : this->mapElements_) {
        mapElement.second->update();

        if (mapElement.second->leftScreen()){
            mapElementDead.push_back(mapElement.first);
        }
    }

    for(auto oneIdDead : mapElementDead){
        this->mapElements_.erase(oneIdDead);
    }
}

void Map::createPlayer(gameParams_t &gameSettings){
    int playerSizeX = gameSettings.playerParams.size_x;
    int playerSizeY = gameSettings.playerParams.size_y;
    string playerSprite = gameSettings.playerParams.sprite;
    this->player = new MapElement(PLAYER, 500, 500, 4, 4, playerSprite, playerSizeX, playerSizeY);
 }



/* //No va mas este
void Stage::createBackground(int oneLevel, int oneStage){

     int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();
    MapElement *background= new MapElement(BACKGROUND,0,0,screen_widht,screen_height,"assets/Stage/Level1/layer_2.png");
    
    lastId_++;
    auto stageData = GameProvider::getConfig()->getSourcesForStage(0,0);

    auto *graphics = new GraphicsScenario(backgroundSource);
    
    background->addAction("Graphics", graphics);

    mapElements_[lastId_] = background; 
}*/

// void Step::createPlayer(){ //no va mas este
//      MapElement* player = new MapElement(PLAYER);
//     lastId_++;

//     Position *initialPosition = new Position(); //Should have a initial player positionHandler
//     Speed *speed = new Speed(); //This should be taken from config
//     Orientation *initialOrientation = new Orientation(); //Should be Front
//     auto *graphics = new GraphicsSpacecraft();
//     auto *movementHandler = new PlayerController(lastId_);

//     player->addState("Position", initialPosition);
//     player->addState("Speed", speed);
//     player->addState("Orientation", initialOrientation);
//     player->addAction("Graphics", graphics);
//     player->addAction("MovementHandler", movementHandler);

//     mapElements_[lastId_] = player;
//  }

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