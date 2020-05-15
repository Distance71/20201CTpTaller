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
    SDL_BlitSurface(loginscreen, NULL, surface, NULL);
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
    
    /***  TODO ESTO ES PARA PROBAR NADA MAS -> Se cambio a ver si funciona el getSourcesForStage */
    stageSource_t background = GameProvider::getConfig()->getSourcesForStage(0,0);
    //background.layer1="assets/Stage/Level1/layer_1.png";
    //background.layer2="assets/Stage/Level1/layer_2.png";
    //background.layer3="assets/Stage/Level1/layer_3.png";
    GraphicsScenario escenario= GraphicsScenario(background);

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();
        
    gameParams_t gameParams = GameProvider::getConfig()->getGameParams();

    this->map_ = new Map(gameParams);

    MapElement nave= MapElement(PLAYER,500,500,4,4,"assets/player.png");
    /*MapElement enemigo1 = MapElement(ENEMY_1,screen_widht+100,200,2,2,"assets/Enemies/enemigo1.png");
    MapElement enemigo2 = MapElement(ENEMY_2,screen_widht+400,screen_height-200,2,2,"assets/Enemies/enemigo2.png");
    MapElement enemigo3 = MapElement(ENEMY_1,screen_widht+800,200,2,2,"assets/Enemies/enemigo1.png");
    MapElement enemigo4 = MapElement(ENEMY_2,screen_widht+100,screen_height-200,2,2,"assets/Enemies/enemigo2.png");
    MapElement enemigo5 = MapElement(ENEMY_1,screen_widht+400,200,2,2,"assets/Enemies/enemigo1.png");
    MapElement enemigo6 = MapElement(ENEMY_2,screen_widht+900,screen_height-200,2,2,"assets/Enemies/enemigo2.png");*/

    currentStep_t current;
    current.level = LEVEL_ONE;
    current.stage = STAGE_ONE;
    current.step = 0;

    while (true){
        
        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type==SDL_QUIT){
                return;
            }
        }
        escenario.update();
        nave.update();
        this->map_->update(current);
        /*enemigo1.update();
        enemigo2.update();
        enemigo3.update();
        enemigo4.update();
        enemigo5.update();
        enemigo6.update();*/

        updateGraphics();  
    }


    //auto gameSettings = GameProvider::getConfig()->getGameSettings();
    //size_t quantityLevels = gameSettings.size(); //See later this, syntax
    //HOTFIX
    //size_t quantityLevels = 1;

    //vector<Level *> levels = map_->getLevels();
    //Make a convertion with actual step to integer

    //for(size_t i = 0; i < quantityLevels; i++){
        //runLevel(i, levels[i]);
    //}
}

void Game::initializeGameParams(){
    //auto gameSettings = GameProvider::getConfig()->getGameSettings();

    //map_ = new Map(gameSettings);
}

void Game::runLevel(currentStep_t actualStep, Level *level){
    //auto gameSettings = GameProvider::getConfig()->getGameSettings();
    //size_t quantityStages = gameSettings[actualStep.level].stagesParams.size();
    //HOTFIX
    size_t quantityStages = 1;
    auto stages = level->getStages();
    
    //Make a convertion with actual step to integer

    for(size_t i = 0; i < quantityStages; i++){
        //runStage(i, stages[i]);
    }
}

void Game::runStage(currentStep_t actualStep, Stage *stage){
    //auto gameSettings = GameProvider::getConfig()->getGameSettings();
    //size_t quantitySteps = gameSettings[actualStep.level][actualStep.step].stepsParams.size();
    //HOTFIX
    size_t quantitySteps = 3;
    vector<Step *> steps = stage->getSteps();

    //Make a convertion with actual step to integer

    for(size_t i = 0; i < quantitySteps; i++){
        //runStep(i, steps[i]);
    }
}

void Game::runStep(currentStep_t actualStep){
    double elaptedTimeMS = GameProvider::getElaptedTimeFPS();

    while(GameProvider::getStatus().normalStatus){ // || funcionFinStep) {
        auto begin = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();   
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        
        clearScene();
        processEvent();

        while(0 >= (ms - elaptedTimeMS)) {
            updateState(actualStep);
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        }
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