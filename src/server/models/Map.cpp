#include "Map.h"
Map::Map(){}

Map::Map(gameParams_t &gameSettings){
    size_t nLevels = gameSettings.levelParams.size();
    Logger::getInstance()->log(DEBUG, "Se crea entidad Map.");
    Logger::getInstance()->log(DEBUG, "Se procesa el Game Setting.");

    for(size_t i = 0; i < nLevels; i++){
        Level *newLevel = new Level(gameSettings.levelParams[i]);
        this->addLevel(newLevel);
    }
}

bool Map::endStep(currentStep_t currentStep){
    return this->levels_[currentStep.level]->endStep(currentStep.stage, currentStep.step);
}

Level::Level(){}

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

Stage::Stage(){}

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

Step::Step(){}

Step::Step(stepParams_t params) {
    size_t nEnemies = params.enemies.size();
    
    for(size_t i = 0; i < nEnemies; i++){
        unsigned int nEnemiesIguales = params.enemies[i].quantity;
        string sprite = params.enemies[i].sprite;
        int size_x = params.enemies[i].size_x;
        int size_y = params.enemies[i].size_y;
        elementType_t typeEnemy = (elementType_t) params.enemies[i].type;
        
        for(unsigned int j = 0; j < nEnemiesIguales; j++){
            //Las posiciones y demas son de prueba
            position_t positionEnemy = getPosition(size_x, size_y);
            MapElement *newEnemy = new MapElement(typeEnemy, positionEnemy, 2, 2, size_x, size_y);
            this->mapElements_.emplace(this->lastId_, newEnemy);
            this->lastId_++;
        }
    }
}

bool Step::endStep(){
    return (this->mapElements_.size() <= GameProvider::getQuantityPlayers());
}

position_t Step::getPosition(int sizeMapElement_x, int sizeMapElement_y){
    position_t positionMapElement;
    int minPosX, maxPosX;
    int minPosY = 0;
    int maxPosY = GameProvider::getHeight() - sizeMapElement_y;
    
    int orientationRand = rand() % 2;

    if (orientationRand == 0){
        positionMapElement.orientation = BACK;//FRONT
        minPosX = GameProvider::getWidth();
        maxPosX = minPosX * 2;
        positionMapElement.axis_x = minPosX + rand()%(maxPosX + 1 - minPosX);
    } else {
        positionMapElement.orientation = FRONT;//BACK
        minPosX = 0 + sizeMapElement_x;
        maxPosX = GameProvider::getWidth();
        positionMapElement.axis_x = -1 * (minPosX + rand()%(maxPosX + 1 - minPosX));
    } 

    positionMapElement.axis_y = minPosY + rand()%(maxPosY + 1 - minPosY);
    
    return positionMapElement;
}

void Map::addLevel(Level *level){
    if(!level){}
    this->levels_.push_back(level);
}

void Level::addStage(Stage *stage){
    if(!stage) {}
    this->stages_.push_back(stage);
}

void Stage::addStep(Step *step){
    if(!step) {}
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

void Map::update(currentStep_t currentStep, Game *game){
    size_t actualLevel = currentStep.level;
        
    this->updatePlayers(game);
    levels_[actualLevel]->update(currentStep, game);
    position_t aux;
    game->sendEvent(new EventMapElementUpdate(END_GRAPHIC, aux)); 
}

void Map::updatePlayers(Game *game){

    for(auto mapElementPlayer : this->players){
        position_t actualPosition = mapElementPlayer.second->getActualPosition();
        Event *eventUpdate = new EventMapElementUpdate(mapElementPlayer.second->getType(), actualPosition);
        game->sendEvent(eventUpdate);
    }
}

void Level::update(currentStep_t currentStep, Game *game){
    size_t actualStage = currentStep.stage;
    stages_[actualStage]->update(currentStep, game);
}

void Stage::update(currentStep_t currentStep, Game *game){
    size_t actualStep = currentStep.step;
    steps_[actualStep]->update(game);
}

void Step::update(Game *game){
    vector<Id> mapElementDead;

    for(auto mapElement : this->mapElements_) {
        mapElement.second->update();
        if (mapElement.second->leftScreen()){
            mapElementDead.push_back(mapElement.first);
        } else {
            position_t actualPosition = mapElement.second->getActualPosition();
            Event *eventUpdate = new EventMapElementUpdate(mapElement.second->getType(), actualPosition);
            game->sendEvent(eventUpdate);
        }
    }

    for(auto oneIdDead : mapElementDead){
        auto it = this->mapElements_.find(oneIdDead);
        if (it !=  this->mapElements_.end()){
            MapElement *enemyDead = this->mapElements_.at(oneIdDead);
            this->mapElements_.erase(oneIdDead);
            delete enemyDead;
        }
               
    }
}

void Map::movePlayer(string user, orientation_t orientation){
    MapElement *onePlayer = this->players[user];
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para mover.");
        return;
    }
    onePlayer->moveTo(orientation);
    Logger::getInstance()->log(DEBUG, "Se mueve el jugador .");
}

void Map::informDisconnection(string username){   
    elementType_t PLAYER_X = this->players[username]->getType();
    elementType_t NEW_TYPE;
    switch (PLAYER_X){
        case PLAYER_1:
            NEW_TYPE = PLAYER_1_OUT;
            break;
        case PLAYER_2:
            NEW_TYPE = PLAYER_2_OUT;
            break;
        case PLAYER_3:
            NEW_TYPE = PLAYER_3_OUT;
            break;
        case PLAYER_4:
            NEW_TYPE = PLAYER_4_OUT;
            break;
    }
    this->players[username]->setType(NEW_TYPE);
}

position_t Map::getInitialPosition(){
    position_t position;
    position.orientation = FRONT;
    position.axis_y = this->loggedPlayers_ * 100 + 50;
    position.axis_x = 50;

    return position;
}

elementType_t Map::getPlayerType(){
    vector<elementType_t> keys;
    keys.push_back(PLAYER_1);
    keys.push_back(PLAYER_2);
    keys.push_back(PLAYER_3);
    keys.push_back(PLAYER_4);
    return keys[this->loggedPlayers_];
}

void Map::informConnection(string username){
    if (this->players.find(username) == this->players.end()) { 
        MapElement *newPlayer = new MapElement(this->getPlayerType(), this->getInitialPosition(), 4, 4, 100, 100); 
        this->players.emplace(username, newPlayer);
        this->loggedPlayers_++;
        return;
    }
    
    elementType_t PLAYER_X = this->players[username]->getType();
    elementType_t NEW_TYPE;
    switch (PLAYER_X){
        case PLAYER_1_OUT:
            NEW_TYPE = PLAYER_1;
            break;
        case PLAYER_2_OUT:
            NEW_TYPE = PLAYER_2;
            break;
        case PLAYER_3_OUT:
            NEW_TYPE = PLAYER_3;
            break;
        case PLAYER_4_OUT:
            NEW_TYPE = PLAYER_4;
            break;
    }
    this->players[username]->setType(NEW_TYPE);
}

void Map::initializeStep(currentStep_t currentStep, Game *game){
    size_t actualLevel = currentStep.level;   

    levels_[actualLevel]->initializeStep(currentStep, game);
}

void Level::initializeStep(currentStep_t currentStep, Game *game){
    size_t actualStage = currentStep.stage;   
    stages_[actualStage]->initializeStep(currentStep, game);
}

void Stage::initializeStep(currentStep_t currentStep, Game *game){
    size_t actualStep = currentStep.step;
    steps_[actualStep]->initializeStep(game);
}

void Step::initializeStep(Game *game){
    // cout << "INITIALIZE STEP " << this->mapElements_.size() << endl;
    for(auto mapElement : this->mapElements_) {
        position_t actualPosition = mapElement.second->getActualPosition();
        char imagePath[100];
        //Event *event = new EventMapElementCreate(mapElement.first, imagePath, actualPosition, spriteSize);
        //game->sendEvent(event);
    }
    // cout << "END INITIALIZE STEP" << endl;
}
