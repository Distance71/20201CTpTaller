// OUTDATED

#include "Game.h"

Game::Game(Server *server){
    this->serverOwn_ = server;
}

Game::~Game(){
}

void Game::run() {
    if (!GameProvider::getStatus().normalStatus)
        return;

    initializeGameParams();
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

    this->sendStartStage(actualStep.level);

    auto stages = level->getStages();
    Logger::getInstance()->log(INFO, "Se comienza el nivel " + to_string(actualStep.level));
    for(size_t i = 0; i < quantityStages; i++){
        actualStep.stage = static_cast<stage_t>(i);
        //TODO revisar sendBackground
        this->sendBackground(actualStep.stage);
        runStage(actualStep, stages[i]);  
    }
    //usleep(3000);
    

    if (GameProvider::getStatus().normalStatus){
        this->sendStageCleared(actualStep.level);
        this->map_->initializePositionPlayers(gameSettings);
    }
}

void Game::runStage(currentStep_t actualStep, Stage *stage){
    auto gameSettings = GameProvider::getConfig()->getGameParams();
    size_t quantitySteps = gameSettings.levelParams[actualStep.level].stagesParams[actualStep.step].stepsParams.size();

    vector<Step *> steps = stage->getSteps();

    Logger::getInstance()->log(DEBUG, "Se comienza el stage " + to_string(actualStep.stage) + " del nivel " + to_string(actualStep.level));
    for(size_t i = 0; i < quantitySteps; i++){
        actualStep.step = i;
        runStep(actualStep);
    }
}

void Game::runStep(currentStep_t actualStep){
    double elaptedTimeMS = GameProvider::getElaptedTimeFPS();

    Logger::getInstance()->log(DEBUG, "Se comienza el step " + to_string(actualStep.step) + " del stage " + to_string(actualStep.stage) + " del nivel " + to_string(actualStep.level));
    
    initializeStep(actualStep);
    
    while(GameProvider::getStatus().normalStatus && !this->map_->endStep(actualStep)){ // || funcionFinStep) {
        auto begin = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();   
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

        while(0 >= (ms - elaptedTimeMS)) { 
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        }
        updateState(actualStep);
    }
}

void Game::initializeStep(currentStep_t actualStep){
    map_->initializeStep(actualStep, this);
}

void Game::updateState(currentStep_t actualStep) {
    map_->update(actualStep, this);
}

void Game::sendStartStage(level_t oneLevel){
    sceneScreen_t pathScreen;

    switch (oneLevel){
        case LEVEL_ONE:
            pathScreen = INIT_STAGE_1;
            break;
        case LEVEL_TWO:
            pathScreen = INIT_STAGE_2;
            break;
        case LEVEL_THREE:
            pathScreen = INIT_STAGE_3;
            break;
        case LEVEL_FOUR:
            pathScreen = INIT_STAGE_4;
            break;
        default:
            pathScreen = INIT_STAGE_DEFAULT;
            break;
    }

    Event* event = new EventSceneAnimation(pathScreen);
    this->sendEvent(event);
    
    usleep(5000000);//5 seg
}

void Game::sendStageCleared(level_t oneLevel){

    sceneScreen_t pathScreen;

    switch (oneLevel){
        case LEVEL_ONE:
            pathScreen = END_STAGE_1;
            break;
        case LEVEL_TWO:
            pathScreen = END_STAGE_2;
            break;
        case LEVEL_THREE:
            pathScreen = END_STAGE_3;
            break;
        case LEVEL_FOUR:
            pathScreen = END_STAGE_4;
            break;
        default:
            pathScreen = END_STAGE_DEFAULT;
            break;
    }

    Event* event = new EventSceneAnimation(pathScreen);
    this->sendEvent(event);
    usleep(5000000);//5 seg;
    
}

void Game::movePlayer(string user, orientation_t orientation){
    this->map_->movePlayer(user, orientation);
}

void Game::sendBackground(size_t numberStage){
    // Event* event;
    // switch(numberStage){
    //     case 1: 
    //         event = new EventSceneAnimation(LEVEL_ONE);
    //         break;
    //     case 2:
    //         event = new EventSceneAnimation(LEVEL_TWO);
    //         break;
    //     case 3:
    //         event = new EventSceneAnimation(LEVEL_THREE);
    //         break;
    //     case 4:
    //         event = new EventSceneAnimation(LEVEL_FOUR);
    //         break;
    // }
    
    // this->sendEvent(event);
}

void Game::sendEvent(Event *event){
    this->serverOwn_->sendToAllUsers(event);
}

void Game::informDisconnection(string username){
    if (this->map_ != NULL) this->map_->informDisconnection(username);
}

void Game::informConnection(string username){
    if (this->map_ != NULL) this->map_->informConnection(username);
}
