#include "Game.h"

Game::Game(Server *server){
    this->serverOwn_ = server;
    initializeGameParams();
}

Game::~Game(){
}

Map* Game::getMap(){
    return map_;
}

void Game::run() {

    usleep(10000);
    
    if (!GameProvider::getStatus().normalStatus)
        return;

    currentStep_t current = {};   

    auto gameSettings = GameProvider::getConfig()->getGameParams();
    size_t quantityLevels = gameSettings.levelParams.size();

    vector<Level *> levels =  map_->getLevels();    
    size_t i = 0;

    while ((i < quantityLevels) && (GameProvider::getStatus().normalStatus)){
        current.level = static_cast<level_t>(i); 
        runLevel(current, levels[i]);
        i++;
    }
}

void Game::initializeGameParams(){
    auto gameSettings = GameProvider::getConfig()->getGameParams();

    map_ = new Map(gameSettings);
}

void Game::runLevel(currentStep_t actualStep, Level *level){
    auto gameSettings = GameProvider::getConfig()->getGameParams();
    size_t quantityStages = gameSettings.levelParams[actualStep.level].stagesParams.size();

    auto stages = level->getStages();
    Logger::getInstance()->log(INFO, "Se comienza el nivel " + to_string(actualStep.level));

    for(size_t i = 0; i < quantityStages; i++){
        actualStep.stage = static_cast<stage_t>(i);

        bool isFinalStage = (i == quantityStages - 1);
        runStage(actualStep, stages[i], isFinalStage);  
    }

    sendEvent(new EventEndGame());

    usleep(5000000);
}

void Game::runStage(currentStep_t actualStep, Stage *stage, bool isFinalStage){
    auto gameSettings = GameProvider::getConfig()->getGameParams();
    size_t quantitySteps = gameSettings.levelParams[actualStep.level].stagesParams[actualStep.step].stepsParams.size();

    this->sendStartStage(actualStep.stage);

    vector<Step *> steps = stage->getSteps();
    this->map_->cleanStage();
    
    Logger::getInstance()->log(DEBUG, "Se comienza el stage " + to_string(actualStep.stage) + " del nivel " + to_string(actualStep.level));
    for(size_t i = 0; i < quantitySteps; i++){
        actualStep.step = i;
        runStep(actualStep);
    }

    if (isFinalStage)
        this->runFinal();

    this->sendStageCleared(actualStep.stage);
    
}

void Game::runStep(currentStep_t actualStep){
    double elaptedTimeMS = GameProvider::getElaptedTimeFPS();

    Logger::getInstance()->log(DEBUG, "Se comienza el step " + to_string(actualStep.step) + " del stage " + to_string(actualStep.stage) + " del nivel " + to_string(actualStep.level));
    srand(time(NULL));
    map_->setTargetsForStep(actualStep, this);

    while(GameProvider::getStatus().normalStatus && !this->map_->endStep(actualStep) && this->map_->playerAlive()){
        updateState(actualStep);
        usleep(18000);
    }
}

void Game::updateState(currentStep_t actualStep) {
    map_->update(actualStep, this);
}

void Game::runFinal(){

    Logger::getInstance()->log(DEBUG, "Se comienza round con Boss");

    while(GameProvider::getStatus().normalStatus && !this->map_->endFinal() && this->map_->playerAlive()){
        map_->updateFinal(this);
        usleep(18000);
    }

   usleep(3000000);//3 seg;
}

void Game::sendStartStage(stage_t stage){
    sceneScreen_t sceneScreen;

    switch (stage){
        case STAGE_ONE:
            sceneScreen = INIT_STAGE_1;
            break;
        case STAGE_TWO:
            sceneScreen = INIT_STAGE_2;
            break;
        case STAGE_THREE:
            sceneScreen = INIT_STAGE_3;
            break;
        case STAGE_FOUR:
            sceneScreen = INIT_STAGE_4;
            break;
        default:
            sceneScreen = INIT_STAGE_DEFAULT;
            break;
    }

    Event* event = new EventSceneAnimation(sceneScreen);
    this->sendEvent(event);
    
    usleep(3000000);//3 seg
}

void Game::sendStageCleared(stage_t stage){

    sceneScreen_t sceneScreen;

    switch (stage){
        case LEVEL_ONE:
            sceneScreen = END_STAGE_1;
            break;
        case LEVEL_TWO:
            sceneScreen = END_STAGE_2;
            break;
        case LEVEL_THREE:
            sceneScreen = END_STAGE_3;
            break;
        case LEVEL_FOUR:
            sceneScreen = END_STAGE_4;
            break;
        default:
            sceneScreen = END_STAGE_DEFAULT;
            break;
    }

    Event* event1 = new EventSceneAnimation(sceneScreen);
    this->sendEvent(event1);
    usleep(3000000);//3 seg;

    Event* event2 = new EventSceneAnimation(SCORE_TABLE);
    this->sendEvent(event2);
    usleep(5000000);
    
}

void Game::movePlayer(string user, orientation_t orientation){
    this->map_->movePlayer(user, orientation);
}

void Game::changeGameModePlayer(string user){
    this->map_->changeGameModePlayer(user);
}

void Game::shootPlayer(string user){
    this->map_->shootPlayer(user);
}

void Game::sendEvent(Event *event){
    this->serverOwn_->sendToAllUsers(event);
}

void Game::sendEventToUser(string username, Event* event){
    this->serverOwn_->sendToUserForUsername(username, event);
}

void Game::informDisconnection(string username){
    Logger::getInstance()->log(DEBUG, "Se informa desconexion en Game");
    this->map_->informDisconnection(username);
}

void Game::informConnection(string username){
    Logger::getInstance()->log(DEBUG, "Se informa conexion en Game");
    this->map_->informConnection(username);
}

