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
    Logger::getInstance()->log(DEBUG, "Se inicializan los graficos de renderer y la window");

    //Inicializo SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::getInstance()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    window_ = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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
    this->map_ = new Map();
}

bool Game::login() {
    string srcSpriteLoginScreen = "assets/LoginScreen/loginScreen.png"; //services -> configurationHandler->get('/loginScreen')
    size_t height = GameProvider::getHeight();
    size_t width = GameProvider::getWidth();

    bool loginDone = false, exit = false;

    Logger::getInstance()->log(INFO, "Se ha entrado en la pantalla de login");

    auto *spriteLoginScreen = new SpriteGenerator(srcSpriteLoginScreen);
    SDL_Rect spriteLoginPositionInScreen = {0, 0, (int) width, (int) height};
    
    
    //Note: Should write an only method
    SDL_RenderCopy(renderer_, spriteLoginScreen->getTexture(), NULL, &spriteLoginPositionInScreen);
    GameProvider::setRenderer(renderer_);

    updateGraphics();
    
    while(!loginDone && GameProvider::getStatus().normalStatus) {
        SDL_Event event;
        if(SDL_PollEvent(&event) && (event.type == SDL_QUIT)) {
            GameProvider::setNormalExitStatus();
            Logger::getInstance()->log(INFO, "El usuario ha cerrado el juego");        
        }
        
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                loginDone = true;
            default:;
        }
    }

    Logger::getInstance()->log(DEBUG, "Se ha pasado la pantalla de login");
    
    return loginDone;
}

void Game::run() {
    if(!GameProvider::getStatus().normalStatus || !login())
        return;

    // double previous = time(NULL);
    // double lag = 0;

    // while(GameProvider::getStatus().normalStatus) {
    //     double current = time(NULL);
    //     double elapsed = current - previous;
    //     previous = current;
    //     lag += elapsed;

    //     SDL_RenderClear(renderer_); //borra el renderer previo
    //     processEvent();

    //     double elaptedTimeMS = GameProvider::getElaptedTimeFPS(); 

    //     while(lag >= elaptedTimeMS) {
    //         updateState();
    //         lag -= elaptedTimeMS;
    //     }
        
    //     updateGraphics();
    // }
}

void Game::processEvent() {
    SDL_Event lastEvent;
    if(SDL_PollEvent(&lastEvent) && (lastEvent.type == SDL_QUIT)) {
        Logger::getInstance()->log(INFO, "Cierre del juego voluntario");
        GameProvider::setNormalExitStatus();
    }
    GameProvider::setLastEvent(lastEvent);
}

void Game::updateState() {
    auto mapElements = map_->getElements();

    // for (auto element : mapElements) {
        
    // }
}

void Game::updateGraphics() {
    SDL_Renderer *actualRenderer = GameProvider::getRenderer();

    SDL_RenderPresent(actualRenderer);
    renderer_ = actualRenderer;
}