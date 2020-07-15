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
    createPlayers(gameSettings);
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
        
        for(unsigned int j = 0; j < nEnemiesIguales; j++){
            //Las posiciones y demas son de prueba
            position_t positionEnemy = getPosition(size_x, size_y);
            MapElement *newEnemy = new MapElement(ENEMY, positionEnemy,2,2,sprite, size_x, size_y);
            this->mapElements_[this->lastId_] = newEnemy;
            this->lastId_++;
        }
    }
}

bool Step::endStep(){
    return (this->mapElements_.empty());
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
        
    //this->player->update();
    levels_[actualLevel]->update(currentStep, game);
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
    // cout << "ENTRO AL UPDATE STEP " << this->mapElements_.size() << endl;
    for(auto mapElement : this->mapElements_) {
        mapElement.second->update();
        // cout << mapElement.first << endl;
        if (mapElement.second->leftScreen()){
            mapElementDead.push_back(mapElement.first);
            Event *eventDead = new EventMapElementDelete(mapElement.first);
            game->sendEvent(eventDead);
        } else {
            position_t actualPosition = mapElement.second->getActualPosition();
            Event *eventUpdate = new EventMapElementUpdate(mapElement.first, actualPosition);
            game->sendEvent(eventUpdate);
        }
    }

    for(auto oneIdDead : mapElementDead){
        MapElement *enemyDead = this->mapElements_.at(oneIdDead);
        this->mapElements_.erase(oneIdDead);
        delete enemyDead;        
    }
}

void Map::createPlayers(gameParams_t &gameSettings){
    size_t cantPlayers = gameSettings.playersParams.size();
    Logger::getInstance()->log(DEBUG, "Se comienza a crear el MapElement para cada jugador.");
    for (size_t i = 0; i < cantPlayers; i++){
        int playerSizeX = gameSettings.playersParams[i].playerParams.size_x;
        int playerSizeY = gameSettings.playersParams[i].playerParams.size_y;
        string playerSprite = gameSettings.playersParams[i].playerParams.sprite;
        Id idPlayer = gameSettings.playersParams[i].id;
        position_t positionPlayer;
        positionPlayer.axis_x = (GameProvider::getWidth() / 3) -  playerSizeX / 2;
        positionPlayer.axis_y = ((GameProvider::getHeight() / 4) * i) / 2;
        positionPlayer.orientation = FRONT;
        this->players[idPlayer] = new MapElement(PLAYER, positionPlayer, 4, 4, playerSprite, playerSizeX, playerSizeY);
    }
}

void Map::initializePositionPlayers(gameParams_t &gameSettings){
    size_t cantPlayers = gameSettings.playersParams.size();
    Logger::getInstance()->log(DEBUG, "Se inicializa la posicion del MapElement para cada jugador.");
    for (size_t i = 0; i < cantPlayers; i++){
        int playerSizeX = gameSettings.playersParams[i].playerParams.size_x;
        int playerSizeY = gameSettings.playersParams[i].playerParams.size_y;
        Id idPlayer = gameSettings.playersParams[i].id;
        position_t positionPlayer;
        positionPlayer.axis_x = (GameProvider::getWidth() / 3) -  playerSizeX / 2;
        positionPlayer.axis_y = ((GameProvider::getHeight() / cantPlayers) * i) / 2;
        State *playerPosition = this->players[idPlayer]->getState<Position>(string("Position"));
        playerPosition->setX(positionPlayer.axis_x);
        playerPosition->setY(positionPlayer.axis_y);
        State *playerOrientation = this->players[idPlayer]->getState<Orientation>(string("Orientation"));
        playerOrientation->setX(FRONT);
    }    
}

void Map::movePlayer(Id idUser, orientation_t orientation){
    MapElement *onePlayer = this->players[idUser];
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para mover.");
        return;
    }
    onePlayer->moveTo(orientation);
    Logger::getInstance()->log(DEBUG, "Se mueve el jugador .");
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
        string sourceSprite = mapElement.second->getImageSource();
        spriteSize_t spriteSize = mapElement.second->getSpriteSize();
        char imagePath[100];
        strcpy(imagePath, sourceSprite.c_str());
        Event *event = new EventMapElementCreate(mapElement.first, imagePath, actualPosition, spriteSize);
        game->sendEvent(event);
    }
    // cout << "END INITIALIZE STEP" << endl;
}
