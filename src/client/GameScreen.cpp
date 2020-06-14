#include "GameScreen.h"

GameScreen::GameScreen(Client *client){
    this->clientOwn = client;

    this->initializeGraphics();
}

GameScreen::~GameScreen(){
    Logger::getInstance()->log(INFO, "Fin del juego");
    Logger::getInstance()->log(DEBUG, "Se destruye renderer y window");

    SDL_DestroyRenderer(this->renderer_);
    SDL_DestroyWindow(this->window_);
    this->renderer_ = nullptr;
    this->window_ = nullptr;

    SDL_Quit();    
}

void GameScreen::initializeGraphics(){
    Logger::getInstance()->log(DEBUG, "Se inicializan los graficos de renderer y la window");

    //Inicializo SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::getInstance()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    //HABRIA QUE VER ESTO
    GameProvider::setWidth(800);
    GameProvider::setHeight(600);

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();
   
    this->window_ = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_widht, screen_height, SDL_WINDOW_SHOWN);

    if(!this->window_) {
        Logger::getInstance()->log(ERROR, string("Error al crear la ventana! SDL_Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    this->renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!this->renderer_) {
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

    GameProvider::setRenderer(this->renderer_);
    GameProvider::setWindow(this->window_);    
}

bool GameScreen::viewLogin() {
    SDL_Window* window = GameProvider::getWindow();
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Surface* loginscreen = IMG_Load("assets/LoginScreen/loginscreen.png");
    if (!loginscreen){
        Logger::getInstance()->log(ERROR, string("Error al cargar el menu principal: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar el menu principal" );
        return false;
    }
    
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

void GameScreen::clearScene(){
    this->renderer_ = GameProvider::getRenderer();
    SDL_SetRenderDrawColor(this->renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->renderer_);
    GameProvider::setRenderer(this->renderer_);
}

void GameScreen::processEvent() {
    SDL_Event lastEvent;
    if(SDL_PollEvent(&lastEvent) && (lastEvent.type == SDL_QUIT)) {
        Logger::getInstance()->log(INFO, "Cierre del juego voluntario");
        GameProvider::setNormalExitStatus();
    }
    GameProvider::setLastEvent(lastEvent);
}

void GameScreen::updateGraphics() {
    SDL_Renderer *actualRenderer = GameProvider::getRenderer();

    SDL_RenderPresent(actualRenderer);
    this->renderer_ = actualRenderer;
}

bool GameScreen::viewStartStage(level_t oneLevel){
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

    SDL_Surface* screenStage = IMG_Load(pathScreen.c_str());
    
    if (!screenStage){
        Logger::getInstance()->log(ERROR, string("Error al cargar la pantalla de comienzo de Stage: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar pantalla de comienzo de Stage para el nivel " + to_string(oneLevel));
        return false;
    }

    return this->waitEnter(screenStage);
}

bool GameScreen::viewStageCleared(level_t oneLevel){

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

    SDL_Surface* screenStageCleared = IMG_Load(pathScreen.c_str());
    
    if (!screenStageCleared){
        Logger::getInstance()->log(ERROR, string("Error al cargar la pantalla StageCleared: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar pantalla StageCleared para el nivel " + to_string(oneLevel));
        return false;
    }

    return this->waitEnter(screenStageCleared);
}

bool GameScreen::waitEnter(SDL_Surface* screen){

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