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

    this->initializeFinalBoss(gameSettings);
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

    this->createBackground();

    size_t quantitySteps = params.stepsParams.size();
    for(size_t i = 0; i < quantitySteps; i++) {
        Step *step = new Step(params.stepsParams[i]);
        this->addStep(step);
    }
}

void Stage::createBackground(){
    unordered_map<layer_t, size_t> layersSpeeds = GameProvider::getLayersSpeeds();
    
     vector <MapElementBackground*>* layersStageOne = new vector <MapElementBackground*>();
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_1, STAGE_ONE, layersSpeeds[LAYER_1]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_2, STAGE_ONE, layersSpeeds[LAYER_2]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_3, STAGE_ONE, layersSpeeds[LAYER_3]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_4, STAGE_ONE, layersSpeeds[LAYER_4]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_5, STAGE_ONE, layersSpeeds[LAYER_5]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_6, STAGE_ONE, layersSpeeds[LAYER_6]));
     layersStageOne->push_back(this->buildStageBackgroundLayer(LAYER_7, STAGE_ONE, layersSpeeds[LAYER_7]));

 
    stagesBackground_.emplace(STAGE_ONE,layersStageOne);
 
    vector <MapElementBackground*>* layersStageTwo = new vector <MapElementBackground*>();
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_1, STAGE_TWO, layersSpeeds[LAYER_1]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_2, STAGE_TWO, layersSpeeds[LAYER_2]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_3, STAGE_TWO, layersSpeeds[LAYER_3]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_4, STAGE_TWO, layersSpeeds[LAYER_4]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_5, STAGE_TWO, layersSpeeds[LAYER_5]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_6, STAGE_TWO, layersSpeeds[LAYER_6]));
     layersStageTwo->push_back(this->buildStageBackgroundLayer(LAYER_7, STAGE_TWO, layersSpeeds[LAYER_7]));

    stagesBackground_.emplace(STAGE_TWO,layersStageTwo);
 
    vector <MapElementBackground*>*layersStageThree = new vector <MapElementBackground*>();
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_1, STAGE_THREE, layersSpeeds[LAYER_1]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_2, STAGE_THREE, layersSpeeds[LAYER_2]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_3, STAGE_THREE, layersSpeeds[LAYER_3]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_4, STAGE_THREE, layersSpeeds[LAYER_4]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_5, STAGE_THREE, layersSpeeds[LAYER_5]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_6, STAGE_THREE, layersSpeeds[LAYER_6]));
    layersStageThree->push_back(this->buildStageBackgroundLayer(LAYER_7, STAGE_THREE, layersSpeeds[LAYER_7]));

    stagesBackground_.emplace(STAGE_THREE,layersStageThree);
 
     vector <MapElementBackground*>* layersStageFour = new vector <MapElementBackground*>();
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_1, STAGE_FOUR, layersSpeeds[LAYER_1]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_2, STAGE_FOUR, layersSpeeds[LAYER_2]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_3, STAGE_FOUR, layersSpeeds[LAYER_3]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_4, STAGE_FOUR, layersSpeeds[LAYER_4]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_5, STAGE_FOUR, layersSpeeds[LAYER_5]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_6, STAGE_FOUR, layersSpeeds[LAYER_6]));
    layersStageFour->push_back(this->buildStageBackgroundLayer(LAYER_7, STAGE_FOUR, layersSpeeds[LAYER_7]));

 
    stagesBackground_.emplace(STAGE_FOUR,layersStageFour);
 }

MapElementBackground* Stage::buildStageBackgroundLayer(layer_t layer, stage_t stage, int speedX){
    return new MapElementBackground(layer, stage, new Speed(speedX, 0), new Position(0, 0));
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
        int healthEnemy = params.enemies[i].health;
        
        for(unsigned int j = 0; j < nEnemiesIguales; j++){
            position_t positionEnemy = getPosition(size_x, size_y);
            MapElement *newEnemy = new MapElement(typeEnemy, positionEnemy, 2, 2, size_x, size_y, healthEnemy);
            this->mapElements_.emplace(this->lastId_, newEnemy);
            this->lastId_++;
        }
    }

    this->updateShift_ = 1;
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

MapElement* Map::getRandomTarget(Game *game){
    unsigned int target = RandomGenerate::generate(GameProvider::getQuantityPlayers()+1);
    //cout << "player target: "<< target << endl;
    if (target == 5)  return nullptr;

    unsigned int count = 0;
    unordered_map<string, MapElement*>::iterator it = game->getMap()->players.begin();
    while(it != this->players.end())
    {
        if (count == target-1) {
            return it->second;
        }
        count++;
        it++;
    }
    //TODO puede no encontrarlo??
    return nullptr;
}

void Map::setTargetsForStep(currentStep_t currentStep, Game *game){
  size_t actualLevel = currentStep.level;
  levels_[actualLevel]->setTargetsForStep(currentStep, game);
}

void Level::setTargetsForStep(currentStep_t currentStep, Game *game){
    size_t actualStage = currentStep.stage;
    stages_[actualStage]->setTargetsForStep(currentStep, game);
}

void Stage::setTargetsForStep(currentStep_t currentStep, Game *game){
    size_t actualStep = currentStep.step;
    steps_[actualStep]->setTargetsForStep(game);
}

void Step::setTargetsForStep(Game *game){
    for(auto mapElement : this->mapElements_) {
        MapElement *target = getRandomTarget(game);
        mapElement.second->setTarget(target);
    }
}

void Map::cleanStage(){
    for (auto onePlayer : this->players){
        onePlayer.second->cleanShoots();
    }
}

void Map::update(currentStep_t currentStep, Game *game){
    size_t actualLevel = currentStep.level;

    levels_[actualLevel]->update(currentStep, game, this->players);
    position_t aux;
    game->sendEvent(new EventMapElementUpdate(END_GRAPHIC, aux)); 
}

void Level::update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players){
    size_t actualStage = currentStep.stage;
    stages_[actualStage]->update(currentStep, game, players);
}

void Stage::updateBackground(Game *game, stage_t stage){
    vector <MapElementBackground*>* vect = this->stagesBackground_.at(stage);
    auto iter = vect->begin();
    while (iter != vect->end()){
        MapElementBackground* layer = *iter;
        int step = layer->getStep();
        layer_t layer_n = layer->getLayer();
        Event *eventUpdate = new EventBackgroundUpdate(layer_n, stage, step);
        game->sendEvent(eventUpdate);
        layer->update();
        iter++;
    }
}

void Stage::update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players){
    size_t actualStep = currentStep.step;
    updateBackground(game, currentStep.stage);
    steps_[actualStep]->update(game, players);
}

void Step::update(Game *game, unordered_map<string, MapElement*> players){
    //Actaulizo posiciones de los jugadores
    
    for(auto mapElementPlayer : players){
        position_t actualPosition = mapElementPlayer.second->getActualPosition();
        Event *eventUpdate = new EventMapElementUpdate(mapElementPlayer.second->getType(), actualPosition);
        game->sendEvent(eventUpdate);
    }
        
    //Actaulizo posiciones enemigos

    vector <Id> mapElementDead;

    for(auto mapElement : this->mapElements_) {
        mapElement.second->update();
        if (!mapElement.second->leftScreen()){
            position_t position = mapElement.second->getActualPosition();
            Event *eventUpdate = new EventMapElementUpdate(mapElement.second->getType(), position);
            game->sendEvent(eventUpdate);
        }
        else{
            mapElementDead.push_back(mapElement.first);
        }
    
    }

    for(auto IdDead : mapElementDead){
        MapElement* deadMapElement = this->mapElements_.at(IdDead);
        this->mapElements_.erase(IdDead);
        delete deadMapElement;
    }

    mapElementDead.clear();


    // Actaulizo proyectiles de los jugadores
    for(auto mapElementPlayer : players){
        vector<MapElement*> projectiles = mapElementPlayer.second->getShoots();
        for (auto projectile : projectiles){
            projectile->update();
            position_t actualPositionProjectile = projectile->getActualPosition();
            Event *eventUpdateProjectile = new EventMapElementUpdate(projectile->getType(), actualPositionProjectile);
            game->sendEvent(eventUpdateProjectile);
        }
    }

    //Actualizo proyectiles de los enemigos
    for(auto mapElement :this->mapElements_){
        vector<MapElement*> projectiles = mapElement.second->getShoots();
         for (auto projectile : projectiles){
            projectile->update();
            position_t actualPositionProjectile = projectile->getActualPosition();
            Event *eventUpdateProjectile = new EventMapElementUpdate(projectile->getType(), actualPositionProjectile);
            game->sendEvent(eventUpdateProjectile);
        }
    }

    //Se revisan colisiones entre jugadores y enemigos
    for(auto mapElementPlayer : players){
        for(auto mapElement :this->mapElements_){
            bool isCollision = mapElementPlayer.second->checkPlayerToEnemyCollision(mapElement.second);
            if(isCollision) {
                killElementWithExplosion(game,mapElement.second);
                //killElementWithExplosion(game, mapElementPlayer.second);
                mapElementDead.push_back(mapElement.first);
                //falta restar vida al jugador
                
            }
        }
    }

    for(auto IdDead : mapElementDead){
        MapElement* deadMapElement = this->mapElements_.at(IdDead);
        this->mapElements_.erase(IdDead);
        delete deadMapElement;
    }

    mapElementDead.clear();
   





    /*vector<Id> mapElementDead;

    for(auto mapElementPlayer : players){
       

        /*for(auto enemy: this->mapElements_) {
            bool isCollision = mapElementPlayer.second->checkPlayerToEnemyCollision(enemy.second);
            if(isCollision) {
                mapElementDead.push_back(enemy.first);
                //informDisconnection(mapElementPlayer.first);
                //killElementWithExplosion(game, mapElementPlayer.second);
                killElementWithExplosion(game, enemy.second);
            }
        }

        Event *eventUpdate = new EventMapElementUpdate(mapElementPlayer.second->getType(), actualPosition);
        game->sendEvent(eventUpdate);
    }

    for(auto mapElement : this->mapElements_) {
        mapElement.second->update();
        position_t position = mapElement.second->getActualPosition();
        mapElement.second->getCollisionRectangle()->setX(position.axis_x); //TODO: Send to other place
        mapElement.second->getCollisionRectangle()->setY(position.axis_y);
        mapElement.second->checkEnemyToPlayersCollisions(players);
        if (mapElement.second->leftScreen()){
            mapElementDead.push_back(mapElement.first);
        } else {

            position_t actualPosition = mapElement.second->getActualPosition();
            vector<MapElement*> projectiles = mapElement.second->getShoots();

            for (auto projectile : projectiles){
                projectile->update();
                mapElement.second->checkEnemyProyectileToPlayersCollisions(players, projectile);
                position_t actualPositionProjectile = projectile->getActualPosition();

                if (this->shouldSend(projectile, actualPositionProjectile)){
                    Event *eventUpdateProjectile = new EventMapElementUpdate(projectile->getType(), actualPositionProjectile);
                    game->sendEvent(eventUpdateProjectile);
                }
            }

            if (this->shouldSend(mapElement.second, actualPosition)){
                Event *eventUpdate = new EventMapElementUpdate(mapElement.second->getType(), actualPosition);
                game->sendEvent(eventUpdate);
            }

        
    }

    */
   
}

bool Step::shouldSend(MapElement* oneMapElement, position_t actualPosition){
    return ((actualPosition.axis_x >= -oneMapElement->getSizeX()) && actualPosition.axis_y <= GameProvider::getWidth());
}

void Step::killElementWithExplosion(Game *game, MapElement *mapElement){
    position_t actualPosition = mapElement->getActualPosition();
    
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_1, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_2, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_3, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_4, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_5, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_6, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_7, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_8, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_9, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_10, actualPosition));
    usleep(100);
    game->sendEvent(new EventMapElementUpdate(EXPLOSION_ANIMATION_11, actualPosition));
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

void Map::shootPlayer(string user){
    MapElement *onePlayer = this->players[user];
    
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para disparar.");
        return;
    }
    
    onePlayer->shoot();
    Logger::getInstance()->log(DEBUG, "Se efectua disparo del jugador.");
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
        player_t onePlayer = GameProvider::getConfig()->getPlayerParam(this->loggedPlayers_);
        MapElement *newPlayer = new MapElement(this->getPlayerType(), this->getInitialPosition(), 4, 4, onePlayer.size_x, onePlayer.size_y, 100, 3); 
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

void Step::initializeStep(Game *game){}

void Map::initializeFinalBoss(gameParams_t &gameSettings){
    enemy_t finalBoss = gameSettings.finalBoss;

    position_t position;
    position.axis_x = GameProvider::getWidth() + finalBoss.size_x;
    position.axis_y = (GameProvider::getHeight() / 2) - (finalBoss.size_y / 2);
    position.orientation = BACK;

    this->finalBoss_ = new MapElement(finalBoss.type, position, 2, 2, finalBoss.size_x, finalBoss.size_y, finalBoss.health);

}

void Map::updateFinal(Game* game){

    this->levels_.back()->updateFinal(game, this->players, this->finalBoss_);

    position_t aux;
    game->sendEvent(new EventMapElementUpdate(END_GRAPHIC, aux)); 
}

void Level::updateFinal(Game* game, unordered_map<string, MapElement*> players, MapElement* finalBoss){

    stage_t actualStage =  static_cast<stage_t>(this->stages_.size() - 1);
    this->stages_.back()->updateFinal(game, players, finalBoss, actualStage);
}


bool Stage::shouldSend(MapElement* oneMapElement, position_t actualPosition){
    return ((actualPosition.axis_x >= -oneMapElement->getSizeX()) && actualPosition.axis_y <= GameProvider::getWidth());
}


void Stage::updateFinal(Game* game, unordered_map<string, MapElement*> players, MapElement* finalBoss, stage_t stage){

    updateBackground(game, stage);

    for(auto mapElementPlayer : players){
        
        position_t actualPosition = mapElementPlayer.second->getActualPosition();

        vector<MapElement*> projectiles = mapElementPlayer.second->getShoots();
        for (auto projectile : projectiles){
            projectile->update();
            position_t actualPositionProjectile = projectile->getActualPosition();

            if (this->shouldSend(projectile, actualPositionProjectile)){
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }            

        }

        Event *eventUpdate = new EventMapElementUpdate(mapElementPlayer.second->getType(), actualPosition);
        game->sendEvent(eventUpdate);
    }

    if (finalBoss != NULL){
        finalBoss->update();
        position_t actualPositionBoss = finalBoss->getActualPosition();   

        vector<MapElement*> projectiles = finalBoss->getShoots();

        for (auto projectile : projectiles){
            projectile->update();
            position_t actualPositionProjectile = projectile->getActualPosition();

            if (this->shouldSend(projectile, actualPositionProjectile)){
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }
        }          

        Event *eventUpdateBoss = new EventMapElementUpdate(finalBoss->getType(), actualPositionBoss);
        game->sendEvent(eventUpdateBoss);   
    }

}