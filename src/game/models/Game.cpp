#include "Game.h"

Game::Game(){
    initializeGraphics();
}

Game::~Game(){
    Logger::getInstance()->log(INFO, "Fin del juego");
    Logger::getInstance()->log(DEBUG, "Se destruye renderer y window");

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    renderer_ = nullptr;
    window_ = nullptr;

    SDL_Quit();
}

void Game::initializeGraphics() {
    /* Lo primer que se hace al inciar el juego es crear un juego,
    al crear un juego se inicializan inmediatamente SDL y se crea una nueva 
    ventana y el renderer. EL renderer se encarga de todo lo que es dibujar
    o mostrar cosas sobre la ventana. Cada vez que queramos hacer algo sobre
    la ventana se hace con el renderer por lo que lo almacenamos en 
    el provider para poder acceder a el en cualquier parte del juego.*/
    
    Logger::getInstance()->log(DEBUG, "Se inicializan los graficos de renderer y la window");

    //Inicializo SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::getInstance()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();
   
    window_ = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,screen_widht, screen_height, SDL_WINDOW_SHOWN);

    if(!window_) {
        Logger::getInstance()->log(ERROR, string("Error al crear la ventana! SDL_Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer_) {
        Logger::getInstance()->log(ERROR, string("Error al crear el renderer SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Logger::getInstance()->log(ERROR, string("SDL_image no se pudo iniciar! SDL_Error: ").append(IMG_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    if (TTF_Init() < 0) {
        Logger::getInstance()->log(ERROR, string("SDL_ttf no se pudo iniciar! SDL_Error: ").append(TTF_GetError()));
        GameProvider::setErrorStatus(TTF_GetError());
        return;
    }

    GameProvider::setRenderer(renderer_);
    GameProvider::setWindow(window_);
}

//Returns true if normal login
bool Game::login() {
    SDL_Window* window = GameProvider::getWindow();
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Surface* loginscreen = IMG_Load( "assets/LoginScreen/loginscreen.png");
    if (!loginscreen){
        Logger::getInstance()->log(ERROR, string("Error al cargar el menu principal: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar el menu principal" );
        return false;
    }
    //SDL_BlitSurface(loginscreen, NULL, surface, NULL);
    // La pantalla de Login se ajusta segun el tamanio de la ventana 
    SDL_BlitScaled(loginscreen, NULL, surface, NULL);
    SDL_UpdateWindowSurface(window);
    while (GameProvider::getStatus().normalStatus){
        processEvent();
        SDL_Event e = GameProvider::getLastEvent();
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
            return true;
    }
}

/*Luego de inicializados SDL y creados la ventana y el renderer
    se llama al metodo run. EL metodo run tendrá el ciclo principal
    del juego.*/
void Game::run() {
    bool normalLogin = login(); //Menu de inicio
    if (!normalLogin || !GameProvider::getStatus().normalStatus)
        return;

    initializeGameParams();

    currentStep_t current = {};   

    auto gameSettings = GameProvider::getConfig()->getGameParams();
    size_t quantityLevels = gameSettings.levelParams.size();

    vector<Level *> levels =  map_->getLevels();

    /*for(size_t i = 0; i < quantityLevels; i++){
        current.level = static_cast<level_t>(i); 
        runLevel(current, levels[i]);
    }*/
    
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

    this->viewStartStage(actualStep.level);
    auto stages = level->getStages();
    Logger::getInstance()->log(INFO, "Se comienza el nivel " + to_string(actualStep.level));
    for(size_t i = 0; i < quantityStages; i++){
        actualStep.stage = static_cast<stage_t>(i);
        this->map_->setStageSource(actualStep.level,actualStep.stage); //crea el escenario
        runStage(actualStep, stages[i]);
    }
    
    if (GameProvider::getStatus().normalStatus){
        this->viewStageCleared(actualStep.level);
        this->map_->initializePositionPlayer(gameSettings);
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
        
        clearScene();
        processEvent();
        (this->map_->getCurrentScenario())->update();
        while(0 >= (ms - elaptedTimeMS)) { // TODO Revisar esto
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        }
        updateState(actualStep);
        
        updateGraphics();
    }
}

void Game::clearScene(){
    renderer_ = GameProvider::getRenderer();
    SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer_);
    GameProvider::setRenderer(renderer_);
}

void Game::processEvent() {
    SDL_Event lastEvent;
    if(SDL_PollEvent(&lastEvent) && (lastEvent.type == SDL_QUIT)) {
        Logger::getInstance()->log(INFO, "Cierre del juego voluntario");
        GameProvider::setNormalExitStatus();
    }
    GameProvider::setLastEvent(lastEvent);
}

void Game::updateState(currentStep_t actualStep) {
    map_->update(actualStep);
}

void Game::updateGraphics() {
    SDL_Renderer *actualRenderer = GameProvider::getRenderer();

    SDL_RenderPresent(actualRenderer);
    renderer_ = actualRenderer;
}

bool Game::viewStartStage(level_t oneLevel){
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

    }

    SDL_Surface* screenStage = IMG_Load(pathScreen.c_str());
    
    if (!screenStage){
        Logger::getInstance()->log(ERROR, string("Error al cargar la pantalla de comienzo de Stage: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar pantalla de comienzo de Stage para el nivel " + to_string(oneLevel));
        return false;
    }

    return this->waitEnter(screenStage);
}

bool Game::viewStageCleared(level_t oneLevel){

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

    }

    SDL_Surface* screenStageCleared = IMG_Load(pathScreen.c_str());
    
    if (!screenStageCleared){
        Logger::getInstance()->log(ERROR, string("Error al cargar la pantalla StageCleared: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar pantalla StageCleared para el nivel " + to_string(oneLevel));
        return false;
    }

    return this->waitEnter(screenStageCleared);
}

bool Game::waitEnter(SDL_Surface* screen){

    this->clearScene();

    SDL_Window* window = GameProvider::getWindow();
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_BlitScaled(screen, NULL, surface, NULL);
    SDL_UpdateWindowSurface(window);
    while (GameProvider::getStatus().normalStatus){
        processEvent();
        SDL_Event e = GameProvider::getLastEvent();
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
            return true;
    }
}