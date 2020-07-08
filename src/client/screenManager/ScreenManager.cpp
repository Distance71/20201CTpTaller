#include "ScreenManager.h"

ScreenManager::ScreenManager(Client *client){
    this->clientOwn_ = client;
    this->quit_ = false;
    this->screenWidth_ = -1;
    this->screenHeight_ = -1;
    this->window_ = nullptr;
    this->renderer_ = nullptr;
    this->menu_ = nullptr;
    this->gameGraphics_=nullptr;
}


ScreenManager::~ScreenManager(){
    if (this->window_){
        Logger::getInstance()->log(INFO, "Se destruye la ventana.");
        delete window_;
    }
    if(this->renderer_){
        Logger::getInstance()->log(INFO, "Se destruye el renderer.");
        delete renderer_;
    }
    if (this->menu_){
        Logger::getInstance()->log(INFO, "Se destruye el menu");
        delete menu_;
    }
}


void ScreenManager::setScreenSizes(int Xsize, int Ysize){
    this->screenWidth_ = Xsize;
    this->screenHeight_= Ysize;
    Logger::getInstance()->log(DEBUG, "Se recibió el tamaño de la pantalla");
}


bool ScreenManager::initializeGraphics(){

    Logger::getInstance()->log(DEBUG, "Se inicializarán los graficos de la aplicación");

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

    Logger::getInstance()->log(INFO, "Se inicializaron los gráficos de la aplicación correctamente");
    
    return true;
}


bool ScreenManager::viewLogin(){
    
    Logger::getInstance()->log(INFO, "Se creará el menu del juego");
    
    this->menu_ = new Menu();

    SDL_Event e; 
    
    while (GameProvider::getStatus().normalStatus){
        
        while (SDL_PollEvent(&e)){
            
            GameProvider::setLastEvent(e);
            
            if (e.type == SDL_QUIT)
                Logger::getInstance()->log(INFO, "El ususario ha cerrado el menu de forma voluntaria");
                delete this->menu_;
                this->menu_=nullptr;
                return false;
            
            this->menu_ -> processEvent();
        }
        
        if (this->menu_->getLoggedInStatus())
            Logger::getInstance()->log(INFO, "El ususario se ha logueado con exito");
            delete this->menu_;
            this->menu_=nullptr;
            return true;

        this->menu_->show();      
    }

    Logger::getInstance()->log(ERROR ,"Se ha cerrado el menu debido a un problema");
    delete this->menu_;
    this->menu_=nullptr;
    return false;
}


void ScreenManager::initGameGraphics(){

    Logger::getInstance()->log(DEBUG, "Se inicia el hilo graficador");
    
    this->gameGraphics_ = new GameGraphics(this->renderer_);
    
    
    while(this->clientOwn_->isConnected() && !this->quit_){
        this->gameGraphics_->update();
    }

    Logger::getInstance()->log(DEBUG, "Finaliza el hilo graficador");

}


void ScreenManager::createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    if(this->gameGraphics_){
        this->gameGraphics_->createEntity(id,source,sizeX,sizeY,posX,posY,orientation);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido crear entidad, llame a initGameGraphics primero");
    }
}


void ScreenManager::updateEntity(IdElement id, int posX, int posY, orientation_t orientation){   
    if(this->gameGraphics_){
        this->gameGraphics_->updateEntity(id,posX,posY,orientation);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido actualizar la entidad, llame a initGameGraphics primero");
    }
}


void ScreenManager::deadEntity(IdElement id){
    if(this->gameGraphics_){
        this->gameGraphics_->deadEntity(id);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido eliminar la entidad, llame a initGameGraphics primero");
    }
}


void ScreenManager::setBackground(stageSource_t background){
    if(this->gameGraphics_){
        this->gameGraphics_->setBackground(background);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar el background, llame a initGameGraphics primero");
    }
}


void ScreenManager::setImage(const string &source){
    if(this->gameGraphics_){
        this->gameGraphics_->setImage(source);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar la imagen, llame a viewloginprimero");
    } 
}


void ScreenManager::setLoginResponse(responseStatus_t response){
    if(this->menu_){
        this->menu_->setLoginResponse(response);
    }
    else{
        Logger::getInstance()->log(DEBUG, "No se ha podido cargar la respuesta en el menu, llame a viewLogin primero");
    } 
}

