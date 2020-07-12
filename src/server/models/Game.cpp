// OUTDATED

#include "Game.h"

Game::Game(Server *server){
    this->serverOwn_ = server;
}

Game::~Game(){
}

/* EL metodo run tendrá el ciclo principal
    del juego.*/
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
        this->sendBackground(actualStep.level,actualStep.stage);
        runStage(actualStep, stages[i]);
    }    
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

void Game::updateState(currentStep_t actualStep) {
    map_->update(actualStep);
}

void Game::sendStartStage(level_t oneLevel){
    string pathScreen;

    switch (oneLevel){
        case LEVEL_ONE:
            pathScreen = "assets/TransitionScreens/Stage1.JPG";
            break;
        case LEVEL_TWO:
            pathScreen = "assets/TransitionScreens/Stage2.JPG";
            break;
        case LEVEL_THREE:
            pathScreen = "assets/TransitionScreens/Stage3.JPG";
            break;
        case LEVEL_FOUR:
            pathScreen = "assets/TransitionScreens/Stage4.JPG";
            break;
        default:
            pathScreen = "assets/TransitionScreens/StageDefault.jpg";
            break;
    }

    char path[pathScreen.size() + 1];
    strcpy(path, pathScreen.c_str());

    Event* event = new EventAnimationInitStage(path);
    this->serverOwn_->sendToAllUsers(event);
    usleep(5000000);//5 seg
}

void Game::sendStageCleared(level_t oneLevel){

    string pathScreen;

    switch (oneLevel){
        case LEVEL_ONE:
            pathScreen = "assets/TransitionScreens/Stage1Cleared.JPG";
            break;
        case LEVEL_TWO:
            pathScreen = "assets/TransitionScreens/Stage2Cleared.JPG";
            break;
        case LEVEL_THREE:
            pathScreen = "assets/TransitionScreens/Stage3Cleared.JPG";
            break;
        case LEVEL_FOUR:
            pathScreen = "assets/TransitionScreens/Stage4Cleared.JPG";
            break;
        default:
            pathScreen = "assets/TransitionScreens/StageDefaultCleared.jpg";
            break;
    }

    char path[pathScreen.size() + 1];
    strcpy(path, pathScreen.c_str());

    Event* event = new EventEndStage(path);
    this->serverOwn_->sendToAllUsers(event);
    
    usleep(5000000);//5 seg
}

void Game::movePlayer(string nameUser, orientation_t orientation){
    this->map_->movePlayer(nameUser, orientation);
}

void Game::sendBackground(size_t numberLevel, size_t numberStage){

    stageSource_t background = GameProvider::getConfig()->getSourcesForStage(numberLevel,numberStage);

    char layerPaths[7][100];
    strcpy(layerPaths[0], background.layer1.c_str());
    strcpy(layerPaths[1], background.layer2.c_str());
    strcpy(layerPaths[2], background.layer3.c_str());
    strcpy(layerPaths[3], background.layer4.c_str());
    strcpy(layerPaths[4], background.layer5.c_str());
    strcpy(layerPaths[5], background.layer6.c_str());
    strcpy(layerPaths[6], background.layer7.c_str());
    
    Event* event = new EventInitStage(layerPaths);
    this->serverOwn_->sendToAllUsers(event);
    
    usleep(2000000);//tiempo para garantizar q le llego a todos
}
