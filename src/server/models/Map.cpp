#include "Map.h"

void killElementWithExplosion(Game *game, MapElement *mapElement){
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
            MapElement *newEnemy = new MapElement(typeEnemy, positionEnemy, 2, 2, size_x, size_y, healthEnemy, 1);
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
    gameZone_t zone = GameProvider::getGameZone();

    int minPosX, maxPosX;

    int orientationRand = rand() % 2;

    if (orientationRand == 0){
        positionMapElement.orientation = BACK;
        minPosX = zone.xEnd;
        maxPosX = zone.xEnd * 2;        
        positionMapElement.axis_x = minPosX + rand()%(maxPosX + 1 - minPosX);

    } else {
        positionMapElement.orientation = FRONT;
        minPosX = zone.xInit + sizeMapElement_x;
        maxPosX = zone.xEnd;  
        positionMapElement.axis_x = -1 * (minPosX + rand()%(maxPosX + 1 - minPosX));
    } 

    positionMapElement.axis_y  = zone.yInit + rand()%(zone.yEnd + 1 - zone.yInit);
    
    if (positionMapElement.axis_y > zone.yEnd -  sizeMapElement_y){
        positionMapElement.axis_y = zone.yEnd -  sizeMapElement_y;
    }

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
        onePlayer.second->cleanCurrentScore();
    }
}

void Map::update(currentStep_t currentStep, Game *game){
    size_t actualLevel = currentStep.level;

    levels_[actualLevel]->update(currentStep, game, this->players);
    position_t aux;
    game->sendEvent(new EventMapElementUpdate(END_GRAPHIC, aux)); 

    this->sendScorePlayers(game);
}

void Level::update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players){
    size_t actualStage = currentStep.stage;
    stages_[actualStage]->update(currentStep, game, players);
}

void Stage::updateBackground(Game *game, stage_t stage){
    try {
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
    catch(const std::out_of_range& oor){
    }
}

void Stage::update(currentStep_t currentStep, Game *game, unordered_map<string, MapElement*> players){
    size_t actualStep = currentStep.step;
    updateBackground(game, currentStep.stage);
    steps_[actualStep]->update(game, players);
}

void Step::update(Game *game, unordered_map<string, MapElement*> players){
    vector <Id> enemiesDead;
    vector <Id> projectilesDead;
    
    //Actualizo posiciones de los jugadores
    for(auto player : players){

        if (player.second->isDead())
            continue;

        if (player.second->shouldGraphed()){
            position_t actualPosition = player.second->getActualPosition();
            Event *eventUpdate = new EventMapElementUpdate(player.second->getType(), actualPosition);
            game->sendEvent(eventUpdate);
        }
    }
        
    //Actualizo posiciones enemigos
    for(auto enemy : this->mapElements_) {
        enemy.second->update();
        bool isDead = enemy.second->isDead();
        if ((!enemy.second->leftScreen()) && (!isDead)){
            position_t position = enemy.second->getActualPosition();
            Event *eventUpdate = new EventMapElementUpdate(enemy.second->getType(), position);
            game->sendEvent(eventUpdate);
        }
        else{
            
            if (isDead){
                killElementWithExplosion(game,enemy.second);
            }

            enemiesDead.push_back(enemy.first);
        }
    
    }

    for(auto IdDead : enemiesDead){
        try {
            MapElement* deadEnemy = this->mapElements_.at(IdDead);
            this->mapElements_.erase(IdDead);
            delete deadEnemy;
        }
        catch(const std::out_of_range& oor){
            continue;
        }
    }

    enemiesDead.clear();


    //Se revisan colisiones entre jugadores y enemigos
    for(auto player : players){

        if (player.second->isDead() || player.second->isDisconnected())
            continue;

        for(auto enemy :this->mapElements_){
            bool isCollision = player.second->checkCollision(enemy.second);
            if(isCollision){
                killElementWithExplosion(game,enemy.second);
                killElementWithExplosion(game,player.second);
                enemiesDead.push_back(enemy.first);
                
                player.second->quitLives();

                if (player.second->isDead()){
                    killElementWithExplosion(game,player.second);

                    game->sendEventToUser(player.first, new EventGameOver());
                }
            }
        }
    }

    for(auto IdDead : enemiesDead){
        try {
            MapElement* deadEnemy = this->mapElements_.at(IdDead);
            this->mapElements_.erase(IdDead);
            delete deadEnemy;
        } catch(const std::out_of_range& oor){
            continue;
        }
    }
    
    enemiesDead.clear();


    // Actualizo proyectiles de los jugadores
    for(auto player: players){
        unordered_map <Id,MapElement*> projectiles = player.second->getShoots();
        for (auto projectile : projectiles){
            projectile.second->update();
            if(!projectile.second->leftScreen()){
                position_t actualPositionProjectile = projectile.second->getActualPosition();
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile.second->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }
            else{
                projectilesDead.push_back(projectile.first);
            }
        }


        for (auto idDead :projectilesDead){
            player.second->eraseProjectile(idDead);
        }
        
        projectilesDead.clear();
    }


    //Actualizo proyectiles de los enemigos
    for(auto enemy :this->mapElements_){
        unordered_map <Id,MapElement*> projectiles = enemy.second->getShoots();
        for (auto projectile: projectiles){
            projectile.second->update();
            if(!projectile.second->leftScreen()){
                position_t actualPositionProjectile = projectile.second->getActualPosition();
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile.second->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }
            else{
                projectilesDead.push_back(projectile.first); 
            }
        }

        for (auto idDead :projectilesDead){
            enemy.second->eraseProjectile(idDead);
        }
        
        projectilesDead.clear(); 
    }
 
    //Reviso si alguna bala de de los enemigos le pega a un jugador
    for(auto enemy: this->mapElements_){
        unordered_map <Id,MapElement*> projectiles = enemy.second->getShoots();
        for (auto player:players){

           if (player.second->isDead() || player.second->isDisconnected())
            continue;

           for (auto projectile: projectiles){
                bool collision = player.second->checkCollision(projectile.second);
                if (collision){
                    
                    projectilesDead.push_back(projectile.first);
                
                    // Le quitamos vida a player
                    enemy.second->attackTo(player.second);

                    if (player.second->isDead()){
                        killElementWithExplosion(game,player.second);
                        game->sendEventToUser(player.first, new EventGameOver());
                    }

                }
            }
        }

        for (auto idDead :projectilesDead){
            enemy.second->eraseProjectile(idDead);
        }
        projectilesDead.clear(); 
    
    }

    //Reviso si alguna bala del jugador le pega a algun enemigo
    for (auto player:players){
        if (player.second->isDead())
            continue;

        unordered_map <Id,MapElement*> projectiles = player.second->getShoots();
        for (auto enemy : this->mapElements_){
            
            for (auto projectile: projectiles){
                
                bool collision =enemy.second->checkCollision(projectile.second);
                if (collision){
                    
                    projectilesDead.push_back(projectile.first);

                    // Le quitamos vida a enemy y suma puntajes al player
                    player.second->attackTo(enemy.second);

                    if (enemy.second->isDead()){
                        enemiesDead.push_back(enemy.first);
                        killElementWithExplosion(game,enemy.second);
                    }

                }
            }
        }

        for (auto idDead :projectilesDead){
            player.second->eraseProjectile(idDead);
        }
        
        projectilesDead.clear();
    }

    for(auto IdDead : enemiesDead){
        try {
            MapElement* deadEnemy = this->mapElements_.at(IdDead);
            this->mapElements_.erase(IdDead);
            delete deadEnemy;
        } catch(const std::out_of_range& oor) {

        }
        
    }
    
    enemiesDead.clear();    

}

bool Step::shouldSend(MapElement* oneMapElement, position_t actualPosition){
    return ((actualPosition.axis_x >= -oneMapElement->getSizeX()) && actualPosition.axis_y <= GameProvider::getWidth());
}

void Map::movePlayer(string user, orientation_t orientation){
    MapElement *onePlayer = this->players[user];
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para mover.");
        return;
    }

    if (!onePlayer->isDead()){
        onePlayer->moveTo(orientation);
        Logger::getInstance()->log(DEBUG, "Se mueve el jugador .");
    }
}

void Map::changeGameModePlayer(string user){
    MapElement *onePlayer = this->players[user];
    
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para cambiar modo de juego.");
        return;
    }
    
    if (!onePlayer->isDead()){
        onePlayer->changeGameMode();
        Logger::getInstance()->log(DEBUG, "Se cambia modo de juego del jugador.");
    }
}

void Map::shootPlayer(string user){
    MapElement *onePlayer = this->players[user];
    
    if (!onePlayer){
        Logger::getInstance()->log(ERROR, "No se encontro el jugador para disparar.");
        return;
    }
    
    if (!onePlayer->isDead()) {
        onePlayer->shoot();
        Logger::getInstance()->log(DEBUG, "Se efectua disparo del jugador.");
    }
}

bool Map::playerAlive(){

    for (auto player : this->players)
        if (!player.second->isDead())
            return true;

    return false;
}

void Map::sendScorePlayers(Game *game){

    for (auto player : this->players){
        elementType_t typePlayer = player.second->getType();
        unsigned int lives = player.second->getLives();
        int health = player.second->getHealth();
        
        int scoreActual = player.second->getCurrentScore() / 500;
        int scoreAcc = player.second->getScoreAcc() / 500;

        Event *eventScoreUpdate = new EventScoreUpdate(typePlayer, lives, health, scoreActual, scoreAcc);
        game->sendEvent(eventScoreUpdate);
    }
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
    this->players[username]->setGameMode(MODE_TEST_GAME);
}

position_t Map::getInitialPosition(){
    position_t position;
    position.orientation = FRONT;
    gameZone_t zone = GameProvider::getGameZone();
    position.axis_y = this->loggedPlayers_ * 100 + 100 + zone.yInit;
    position.axis_x = 250;

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
    this->players[username]->setGameMode(MODE_NORMAL_GAME);
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

    this->finalBoss_ = new MapElement(finalBoss.type, position, 3, 3, finalBoss.size_x, finalBoss.size_y, finalBoss.health);

}

bool Map::endFinal(){
    return this->finalBoss_->isDead();
}

void Map::updateFinal(Game* game){

    if (!this->hasSetTargetFinal){
        this->hasSetTargetFinal = true;
        for (auto player : this->players)
            this->finalBoss_->setTarget(player.second);
    }

    this->levels_.back()->updateFinal(game, this->players, this->finalBoss_);

    position_t aux;
    game->sendEvent(new EventMapElementUpdate(END_GRAPHIC, aux)); 

    this->sendScorePlayers(game);
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

    vector <Id> projectilesDead;

    //Actualizo posiciones de los jugadores
    for(auto player : players){

        if (player.second->isDead())
            continue;

        position_t actualPosition = player.second->getActualPosition();
        Event *eventUpdate = new EventMapElementUpdate(player.second->getType(), actualPosition);
        game->sendEvent(eventUpdate);
    }

    //Actualizo posicion del Jefe
    if (finalBoss != NULL){
        finalBoss->update();

        if (finalBoss->isDead()){
            killElementWithExplosion(game, finalBoss);
            // delete FInalBoss
        } else {
            position_t position = finalBoss->getActualPosition();
            Event *eventUpdateBoss = new EventMapElementUpdate(finalBoss->getType(), position);
            game->sendEvent(eventUpdateBoss);
        }
    }

    //Reviso colisiones entre jugadores y el jefe
    for (auto player : players){

        if (player.second->isDead() || player.second->isDisconnected())
            continue;

        bool isCollision = player.second->checkCollision(finalBoss);
        if (isCollision){
            // Como resolver que pasa con el Jefe Final
            bool isBossDead = finalBoss->reduceHealth(50);

            if (isBossDead){
                killElementWithExplosion(game, finalBoss);
            }

            player.second->quitLives();

            if (player.second->isDead()){
                killElementWithExplosion(game,player.second);
                game->sendEventToUser(player.first, new EventGameOver());
            }
        }
    }

    //Actualizo proyectiles de los jugadores
    for(auto player: players){
        
        unordered_map <Id,MapElement*> projectiles = player.second->getShoots();
        for (auto projectile : projectiles){
            projectile.second->update();
            if(!projectile.second->leftScreen()){
                position_t actualPositionProjectile = projectile.second->getActualPosition();
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile.second->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }
            else{
                projectilesDead.push_back(projectile.first);
            }
        }


        for (auto idDead :projectilesDead){
            player.second->eraseProjectile(idDead);
        }
        projectilesDead.clear();
    }

    //Actualizo proyectiles del jefe
    if (finalBoss != NULL){
        unordered_map <Id,MapElement*> projectiles = finalBoss->getShoots();
         for (auto projectile: projectiles){
            projectile.second->update();
            if(!projectile.second->leftScreen()){
                position_t actualPositionProjectile = projectile.second->getActualPosition();
                Event *eventUpdateProjectile = new EventMapElementUpdate(projectile.second->getType(), actualPositionProjectile);
                game->sendEvent(eventUpdateProjectile);
            }
            else{
                projectilesDead.push_back(projectile.first); 
            }
        }

        for (auto idDead :projectilesDead){
            finalBoss->eraseProjectile(idDead);
        }
        
        projectilesDead.clear(); 
    }    

    //Reviso si alguna bala del jefe le pega a un jugador
    if (finalBoss != NULL){
       unordered_map <Id,MapElement*> projectiles = finalBoss->getShoots();
        for (auto player:players){

            if (player.second->isDead() || player.second->isDisconnected())
                continue;

           for (auto projectile: projectiles){
                bool collision = player.second->checkCollision(projectile.second);
                if (collision){
                    projectilesDead.push_back(projectile.first);
                
                    // Le quitamos vida a player
                    finalBoss->attackTo(player.second);

                    if (player.second->isDead()){
                        killElementWithExplosion(game,player.second);
                        game->sendEventToUser(player.first, new EventGameOver());
                    }
                }
            }
        }

        for (auto idDead :projectilesDead){
            finalBoss->eraseProjectile(idDead);
        }
        projectilesDead.clear(); 
    }

    //Reviso si alguna bala del jugador le pega al jefe
    for (auto player : players){
        unordered_map <Id,MapElement*> projectiles = player.second->getShoots();
       
        for (auto projectile : projectiles){
            bool collision = finalBoss->checkCollision(projectile.second);
            if (collision){
                projectilesDead.push_back(projectile.first);

                // Le quitamos vida al jefe y suma puntajes al player
                player.second->attackTo(finalBoss);
            }
        }

        for (auto idDead :projectilesDead){
            player.second->eraseProjectile(idDead);
        }
        
        projectilesDead.clear();
    }

}
