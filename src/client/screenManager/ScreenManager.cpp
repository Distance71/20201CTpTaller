#include "ScreenManager.h"
#include <stdio.h>
ScreenManager::ScreenManager(Client *client){
    this->clientOwn_ = client;
    this->screenWidth_ = -1;
    this->screenHeight_ = -1;
    this->window_ = nullptr;
    this->renderer_ = nullptr;
    this->gameGraphics_ = nullptr;
}


ScreenManager::~ScreenManager(){
    if (this->window_){
        Logger::getInstance()->log(DEBUG, "Se destruye la ventana.");
        SDL_DestroyWindow(this->window_);
    }
    if(this->renderer_){
        Logger::getInstance()->log(DEBUG, "Se destruye el renderer.");
        SDL_DestroyRenderer(this->renderer_);
    }
    if (this->menu_){
        Logger::getInstance()->log(DEBUG, "Se destruye el menu");
        delete this->menu_;
    }
    if (this->gameGraphics_){
        Logger::getInstance()->log(DEBUG, "Se destruyen los graficos");
        delete this->gameGraphics_;
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
    bool r2 = initGraphicsMenu();
    bool r3 = initGameGraphics();
    
    if(r1 && r2 && r3){
        Logger::getInstance()->log(DEBUG, "Se inicializarán los graficos del juego correctamente");
        return true;
    }
    else{
        Logger::getInstance()->log(ERROR, "No se pudieron inicializar graficos");
        return false;
    }
}


bool ScreenManager::initSDL(){
    if (this->screenWidth_<0 || this->screenHeight_<0){
        Logger::getInstance()->log(ERROR, "No se han podido inicializar gráficos debido a que la dimensiones de la ventana no son válidas");
        return false;
    }

    if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO )  < 0) {
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
    this->loading_ = new Sprite("assets/TransitionScreens/loading.png");
    
    SDL_RenderCopy(this->renderer_,this->loading_->getTexture(),NULL,NULL);
    SDL_RenderPresent(this->renderer_);
    
    return true;
}


bool ScreenManager::initGraphicsMenu(){
    
    Logger::getInstance()->log(INFO, "Se creará el Menu del juego");

    this->menu_ = new GraphicsMenu(this->clientOwn_);

    if(!this->menu_){
         Logger::getInstance()->log(ERROR, "No se pudo inicializar el Menu.");
         return false;
    }
    else{
        Logger::getInstance()->log(DEBUG, "El Menu se creó correctamente.");
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


void ScreenManager::updateEntity(elementType_t type, position_t position){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un MapElement en ScreenManager");

    if(this->gameGraphics_){
        this->gameGraphics_->updateEntity(type, position);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido actualizar la entidad, no se han inicializado graficos");
    }
}

void ScreenManager::updateMusic(musicType_t type){
    Audio::getInstance()->playEffect(EXPLOSION);
}

void ScreenManager::updateBackgroundLayer(layer_t layer, stage_t stage, int step){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un BackgroundLayer en ScreenManager");

    if(this->gameGraphics_){
        this->gameGraphics_->updateBackgroundLayer(layer,stage,step);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido actualizar la entidad, no se han inicializado graficos");
    }
}

void ScreenManager::setImage(sceneScreen_t scene){
    Logger::getInstance()->log(DEBUG, "Se va a cargar imagen de fondo en ScreenManager");
    if(this->gameGraphics_){
        this->gameGraphics_->setImage(scene);
        this->gameGraphics_->setAudio(scene);
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
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar la respuesta en el GraphicsMenu, no se han inicializado graficos");
    } 
}

GraphicsMenu* ScreenManager::getGraphicsMenu(){
    return this->menu_;
}

static void* viewLoginThread(void* arg){
    ScreenManager* screenManager = (ScreenManager*) arg;
    Client* client = screenManager->getClient();
    GraphicsMenu* menu = screenManager->getGraphicsMenu();
    SDL_Event e;
    while (!client->isLoggedIn() && client->isConnected()){
        while (SDL_PollEvent(&e)){
            GameProvider::setLastEvent(e);
            if (e.type == SDL_QUIT){
                Logger::getInstance()->log(INFO, "El usuario ha cerrado el juego de forma voluntaria");
                client->disconnect();
                return nullptr;
            }
            menu->processEvent();
        }
        menu->checkStatus();
        menu->show();
    }
    
    SDL_RenderClear(GameProvider::getRenderer());  
    client->runDetectEventThread();
}



void ScreenManager::viewLogin(){
    pthread_t viewLogin;
    pthread_create(&viewLogin, NULL, viewLoginThread, this);
}

void ScreenManager::viewEndGameScreen(){
    this->gameGraphics_->setImage(END_GAME_ANIMATION);
}

void ScreenManager::viewGameOverScreen(){
    this->gameGraphics_->setImage(GAME_OVER_ANIMATION);
}

Client* ScreenManager::getClient(){
    return this->clientOwn_;
}


SDL_Renderer* ScreenManager::getRenderer(){
    return this->renderer_;
}

void ScreenManager::ServerDisconnection(){
    this->gameGraphics_->setImage(SERVER_DISCONNECTION);
}

void ScreenManager::updateScore(elementType_t player,unsigned int lives,int health,int score){
    this->gameGraphics_->updateScore(player,lives,health,score);
}