#include "ScreenManager.h"
#include <stdio.h>
ScreenManager::ScreenManager(Client *client){
    this->clientOwn_ = client;
    this->screenWidth_ = -1;
    this->screenHeight_ = -1;
    this->window_ = nullptr;
    this->renderer_ = nullptr;
    this->gameGraphics_ = nullptr;
    this->waiting_ = false;
}


ScreenManager::~ScreenManager(){
    if (this->window_){
        Logger::getInstance()->log(INFO, "Se destruye la ventana.");
        SDL_DestroyWindow(this->window_);
    }
    if(this->renderer_){
        Logger::getInstance()->log(INFO, "Se destruye el renderer.");
        SDL_DestroyRenderer(this->renderer_);
    }
    if (this->menu_){
        Logger::getInstance()->log(INFO, "Se destruye el menu");
        delete menu_;
    }
}


void ScreenManager::setScreenSizes(int Xsize, int Ysize){
    if (this->window_){
        if (Xsize>0 && Ysize>0){
            SDL_SetWindowSize(this->window_,Xsize,Ysize);
            this->screenWidth_=Xsize;
            this->screenHeight_ = Ysize;
            GameProvider::setWidth(Xsize);
            GameProvider::setHeight(Ysize);
            SDL_RenderSetLogicalSize(this->renderer_, Xsize,Ysize);
            Logger::getInstance()->log(DEBUG, "Se cambió el tamaño de la pantalla");
        }
        else{
            Logger::getInstance()->log(DEBUG, "No se pudo cambiar el damaño de la ventana, las dimensiones no son válidas");
        }
    }
    this->screenWidth_ = Xsize;
    this->screenHeight_= Ysize;
    GameProvider::setWidth(Xsize);
    GameProvider::setHeight(Ysize);
    Logger::getInstance()->log(DEBUG, "Se preestablece el tamaño de la ventana");
}


bool ScreenManager::initializeGraphics(){
    Logger::getInstance()->log(DEBUG, "Se inicializarán los graficos del juego con las dimensiones de pantalla preestablecidas");
    bool r1 = initSDL();
    bool r2 = initMenu();
    bool r3 = initGameGraphics();
    
    if(r1 && r2 && r3){
        Logger::getInstance()->log(DEBUG, "Se inicializarán los graficos del juego correctamente");
        runScreenGraphicsThread();
        return true;
    }
    else{
        Logger::getInstance()->log(ERROR, "No se pudieron inicializar graficos");
        return false;
    }
}


static void* screenGraphicsThread(void* arg){
    
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de presentación en pantalla");
    
    ScreenManager* screenManager = (ScreenManager*) arg;
    SDL_Renderer* renderer = screenManager->getRenderer();
    Client* client = screenManager->getClient();

    while (client->isConnected()){
        SDL_RenderPresent(renderer);
        usleep(10000);
    } 

    Logger::getInstance()->log(DEBUG, "Finaliza el hilo de presentación en pantalla");

    return nullptr;
}


void ScreenManager::runScreenGraphicsThread(){
    pthread_t screenGraphics;
    pthread_create(&screenGraphics,NULL,screenGraphicsThread,this);

}

bool ScreenManager::initSDL(){
    if (this->screenWidth_<0 || this->screenHeight_<0){
        Logger::getInstance()->log(ERROR, "No se han podido inicializar gráficos debido a que la dimensiones de la ventana no son válidas");
        return false;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::getInstance()->log(ERROR, string("Error al inicializar SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return false;
    }
    
    this->window_ = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,this->screenWidth_,this->screenHeight_, SDL_WINDOW_SHOWN);
    
    if(!this->window_) {
        Logger::getInstance()->log(ERROR, string("Error al crear la ventana! SDL_Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return false;
    }

    GameProvider::setWindow(this->window_);

    this->renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!this->renderer_) {
        Logger::getInstance()->log(ERROR, string("Error al crear el renderer SDL! Error: ").append(SDL_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return false;
    }

    GameProvider::setRenderer(this->renderer_);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Logger::getInstance()->log(ERROR, string("SDL_image no se pudo iniciar! SDL_Error: ").append(IMG_GetError()));
        GameProvider::setErrorStatus(SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        Logger::getInstance()->log(ERROR, string("SDL_ttf no se pudo iniciar! SDL_Error: ").append(TTF_GetError()));
        GameProvider::setErrorStatus(TTF_GetError());
        return false;
    }

    return true;
}


bool ScreenManager::initMenu(){
    
    Logger::getInstance()->log(INFO, "Se creará el menu del juego");

    this->menu_ = new Menu(this->clientOwn_);

    if(!this->menu_){
         Logger::getInstance()->log(ERROR, "No se pudo inicializar el menu.");
         return false;
    }
    else{
        Logger::getInstance()->log(DEBUG, "El menu se creó correctamente.");
    }

    return true;

}


bool ScreenManager::initGameGraphics(){
    Logger::getInstance()->log(DEBUG, "Se crea el la estructura gameGraphics");
    
    this->gameGraphics_ = new GameGraphics(this->renderer_);
    
    if (!gameGraphics_){
        Logger::getInstance()->log(ERROR," No se pudo crear la estructura gameGraphics");
        return false;
    }
   
    Logger::getInstance()->log(DEBUG, "la estructura gameGraphics se creó correctamente");
    return true;
}

void ScreenManager::graphic(){

    Logger::getInstance()->log(DEBUG, "Se inicia el hilo graficador");

    while(this->clientOwn_->isConnected()) {

        this->gameGraphics_->update();
    }
        

    Logger::getInstance()->log(DEBUG, "Finaliza el hilo graficador");
}

void ScreenManager::updateEntity(elementType_t type, position_t position){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un MapElement en ScreenManager");

    if(this->gameGraphics_){
        this->gameGraphics_->updateEntity(type, position);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido actualizar la entidad, no se han inicializado graficos");
    }
}

void ScreenManager::setBackground(level_t level){
    Logger::getInstance()->log(DEBUG, "Se va a setear un background en ScreenManager");
    if(this->gameGraphics_){
        this->gameGraphics_->setBackground(level);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar el background,  no se han inicializado graficos");
    }
}


void ScreenManager::setImage(sceneScreen_t scene){
    Logger::getInstance()->log(DEBUG, "Se va a cargar imagen de fondo en ScreenManager");
    if(this->gameGraphics_){
        this->gameGraphics_->setImage(scene);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar la imagen,  no se han inicializado graficos");
    } 
}


void ScreenManager::setLoginResponse(responseStatus_t response){
    if(this->menu_){
        this->menu_->setLoginResponse(response);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar la respuesta en el menu, no se han inicializado graficos");
    } 
}

bool ScreenManager::viewLogin(){
    Logger::getInstance()->log(DEBUG, "Se va a mostrar el login");
    SDL_Event e; 
    
    while (true){
        
        while (SDL_PollEvent(&e)){
            
            GameProvider::setLastEvent(e);
            
            if (e.type == SDL_QUIT){
                Logger::getInstance()->log(INFO, "El usuario ha cerrado el menu de forma voluntaria");
                return false;
            }
            this->menu_->processEvent();
        }
        
        if (this->menu_->getLoggedInStatus()){
            Logger::getInstance()->log(DEBUG, "El usuario se ha logueado con exito en ScreenManager");
            return true;
        }  
        this->menu_->show();
    }

    Logger::getInstance()->log(ERROR ,"Se ha cerrado el menu debido a un problema");
    SDL_RenderClear(this->renderer_);
    return false;
}


int ScreenManager::waitForPlayers(){
    Logger::getInstance()->log(DEBUG, "Se esperaran jugadores en ScreenManager");
    if(!this->gameGraphics_){
        Logger::getInstance()->log(DEBUG,"No se puede presentar la pantalla de espera, no se han inicializado gráficos");
        return -1;
    }
    else{
        SDL_Event e;
        Logger::getInstance()->log( DEBUG ,"Se esperan jugadores");
        this->waiting_= false;
        this->gameGraphics_->setImage(WAITING_PLAYERS);
        // while(this->waiting_){
        //     while (SDL_PollEvent(&e)){
        //         if (e.type == SDL_QUIT){
        //             Logger::getInstance()->log(INFO, "El usuario ha cerrado el juego mientras se esperaban jugadores");
        //             SDL_RenderClear(this->renderer_);
        //             return 0;
        //         }
        //     }
        //     this->gameGraphics_->update();
        // }
        return 1;
    }
}

void ScreenManager::stopWaiting(){
    this->waiting_= false;
}

void ScreenManager::viewEndGameScreen(){
    this->gameGraphics_->setImage(END_GAME_ANIMATION);
    this->gameGraphics_->update();
    SDL_Delay(3000);
}

Client* ScreenManager::getClient(){
    return this->clientOwn_;
}


SDL_Renderer* ScreenManager::getRenderer(){
    return this->renderer_;
}