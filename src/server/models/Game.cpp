// OUTDATED

#include "Game.h"

Game::Game(){
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
        this->map_->setStageSource(actualStep.level,actualStep.stage); //crea el escenario
        runStage(actualStep, stages[i]);
    }    
    if (GameProvider::getStatus().normalStatus){
        this->viewStageCleared(actualStep.level);

        //TODO este initializePositionPlayer nose q hace
        //this->map_->initializePositionPlayer(gameSettings);
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
        
        // TODO creo aca hay q escuchar todos los eventos de los jugadores
        clearScene();
        processEvent();   
        //***


        // TODO revisar esto. yo quite getCurrentScenario por q era algo de la vista
        //(this->map_->getCurrentScenario())->update();
        //***

        while(0 >= (ms - elaptedTimeMS)) { // TODO Revisar esto
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        }
        updateState(actualStep);
    }
}

void Game::clearScene(){
    // renderer_ = GameProvider::getRenderer();
    // SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(renderer_);
    // GameProvider::setRenderer(renderer_);
   
    //TODO Revisar si esto dispara algun evento, borrar lo de arriba
    //Event* event = new Event???(pathScreen.c_str());
    //response_t response = user->sendMessage(event);
}

void Game::processEvent() {
    // SDL_Event lastEvent;
    // if(SDL_PollEvent(&lastEvent) && (lastEvent.type == SDL_QUIT)) {
    //     Logger::getInstance()->log(INFO, "Cierre del juego voluntario");
    //     GameProvider::setNormalExitStatus();
    // }
    // GameProvider::setLastEvent(lastEvent);

    //TODO Revisar si esto dispara algun evento,
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

    //Event* event = new EventAnimationInitStage(pathScreen.c_str());
    //TODO Mandar a todos los usuarios esta pantalla
    //response_t response = user->sendMessage(event);
    usleep(50000);
}

void Game::viewStageCleared(level_t oneLevel){

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

    //Event* event = new EventAnimationInitStage(pathScreen.c_str());
    //TODO Mandar a todos los usuarios esta pantalla
    //response_t response = user->sendMessage(event);
     usleep(50000);
}