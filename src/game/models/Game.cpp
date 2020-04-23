#include "Game.h"

Game::Game(){
    initializeGraphics();
}

Game::~Game(){
    GameProvider::getLogger()->log(INFO, "Fin del juego");
    GameProvider::getLogger()->log(DEBUG, "Se destruye renderer y window");

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    renderer_ = nullptr;
    window_ = nullptr;

    SDL_Quit();
}

void Game::initializeGraphics() {
    GameProvider::getLogger()->log(DEBUG, "Se inicializan los graficos de renderer y la window");

    //Inicializo SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        GameProvider::getLogger()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    window_ = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window_) {
        GameProvider::getLogger()->log(ERROR, string("Error al crear la ventana! SDL_Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer_) {
        GameProvider::getLogger()->log(ERROR, string("Error al crear el renderer SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        GameProvider::getLogger()->log(ERROR, string("SDL_image no se pudo iniciar! SDL_Error: ").append(IMG_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return;
    }

    GameProvider::setRenderer(renderer_);
}

bool Game::login() {
    string srcSpriteLoginScreen = "assets/LoginScreen/loginScreen.png"; //services -> configurationHandler->get('/loginScreen')
    size_t height = GameProvider::getHeight();
    size_t width = GameProvider::getWidth();
    //auto *login = map_.createMapElement(); //Debi hacer con esto, pero no tenia tiempo

    bool loginDone = false, exit = false;

    GameProvider::getLogger()->log(INFO, "Se ha entrado en la pantalla de login");

    auto *spriteLoginScreen = new SpriteGenerator(srcSpriteLoginScreen);
    SDL_Rect spriteLoginPositionInScreen = {0, 0, (int) width, (int) height};
    //Note: Should write an only method
    SDL_RenderCopy(renderer_, spriteLoginScreen->getTexture(), NULL, &spriteLoginPositionInScreen);
    GameProvider::setRenderer(renderer_);

    while(!loginDone && GameProvider::getStatus().normalStatus) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT) {
            GameProvider::setNormalExitStatus();
            GameProvider::getLogger()->log(INFO, "El usuario ha cerrado el juego");        
        }
        
        switch (event.key.keysym.sym) {
            case SDLK_KP_ENTER:
                loginDone = true;
            default:;
        }

        updateGraphics();
    }

    GameProvider::getLogger()->log(DEBUG, "Se ha pasado la pantalla de login");
}

void Game::run() {
    if(!GameProvider::getStatus().normalStatus || !login())
        return;
    
    while(GameProvider::getStatus().normalStatus) {
        SDL_RenderClear(renderer_); //borra el renderer previo
        processEvent();
        updateState();
        updateGraphics();
    }
}

void Game::processEvent() {
    SDL_Event lastEvent;
    if(SDL_PollEvent(&lastEvent) && (lastEvent.type == SDL_QUIT)) {
        GameProvider::getLogger()->log(INFO, "Cierre del juego voluntario");
        GameProvider::setNormalExitStatus();
    }
    GameProvider::setLastEvent(lastEvent);
}

void Game::updateState() {
    auto mapElements = map_.getElements();

    // for (auto element : mapElements) {
        
    // }
}

void Game::updateGraphics() {
    SDL_Renderer *actualRenderer = GameProvider::getRenderer();

    SDL_RenderPresent(actualRenderer);
    renderer_ = actualRenderer;
}