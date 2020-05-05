#include "Game.h"
#include "../graphics/GraphicsScenario.h"

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

bool Game::login() {
    bool quit=false;
    SDL_Window* window= GameProvider::getWindow();
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Surface* loginscreen = NULL;
    loginscreen = IMG_Load( "assets/LoginScreen/loginscreen.png");
    if (!loginscreen){
        Logger::getInstance()->log(ERROR, string("Error al cargar el menu principal: ").append(IMG_GetError()));
        GameProvider::setErrorStatus("Error al cargar el menu principal" );
        return true;
    }
    SDL_BlitSurface( loginscreen, NULL, surface, NULL );
    SDL_UpdateWindowSurface(window);
    while (true){
        processEvent();
        SDL_Event e = GameProvider::getLastEvent();
        if(e.type == SDL_KEYDOWN & e.key.keysym.sym == SDLK_RETURN)
            return quit;
    }
}

    /*LOGIN ANTERIOR:
bool Game::login() {
    bool loginDone = false, exit = false;
    
    string srcSpriteLoginScreen = "assets/LoginScreen/loginScreen.png"; //services -> configurationHandler->get('/loginScreen')
    size_t height = GameProvider::getHeight();
    size_t width = GameProvider::getWidth();

    

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
}*/

GraphicsScenario Game::play_level(int stage){
    /* Cuando se incia el nivel lo primero que se hace es crear el mapa
    para ese nivel*/
    //Map map_;
    // static GraphicsScenario graphics_scenario(LEVEL_ONE);
    // return graphics_scenario;
}



void Game::run(){
    /*Luego de inicializados SDL y creados la ventana y el renderer
    se llama al metodo run. EL metodo run tendrá el ciclo principal
    del juego.*/

    /* En primer lugar se muestra el menu principal hasta el que usuario
    desee comenzar la partida*/
    bool quit = login();
    /* Si entramos  es porque el usuario presiono enter e iniciamos el
    ciclo principal del juego. sino entramos es porque el usuario decidió cerrar el juego*/
    //if (!quit){
        int number_of_stages = 1; /* obenerlo de la configuración despues*/
        int stage = 0;
        /* si en algun momento se cerro el juego quit pasara a ser true*/
        GraphicsScenario graphicsScenario(LEVEL_ONE);
        //while (!quit){
            // stage += 1;
            // if (stage > number_of_stages){
            //     /* aca podemos preguntar si quiere volver a jugar*/
            //     quit = true;
            // }
            
            //GraphicsScenario graphics_scenario = play_level(stage);
          //  graphics_scenario.update();
            /*si completa el nivel pasamos al siguiente a menos que no haya más*/
        //}
        /* Se salio del while porque el usuario decidió cerrar el juego
        o lo terminó y no quiere volver a jugar*/
    //}
//}
   
    /*if(!GameProvider::getStatus().normalStatus || !login())
        return;*/

    //  double previous = time(NULL);
    //double lag = 0;

    double elaptedTimeMS = GameProvider::getElaptedTimeFPS(); 

    while(GameProvider::getStatus().normalStatus) {
        auto begin = chrono::high_resolution_clock::now();
        auto end = chrono::high_resolution_clock::now();   
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

         //double elapsed = current - previous;
         //previous = current;
         //lag += elapsed;
        renderer_ = GameProvider::getRenderer();
        SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer_); //borra el renderer previo
        GameProvider::setRenderer(renderer_);
        processEvent();

        while(0 >= (ms - elaptedTimeMS)) {
            //updateState();
            end = chrono::high_resolution_clock::now();
            dur = end - begin;
            ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        }
        graphicsScenario.update();
        updateGraphics();
    }
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