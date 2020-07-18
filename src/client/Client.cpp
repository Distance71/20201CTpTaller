#include "Client.h"

Client::Client(string ipHost,size_t port){
    this->connected_ = false;
    this->ipHost_ = ipHost;
    this->port_ = port;
    this->screenManager_= new ScreenManager(this);
    this->transmitionManager_ = new ClientTransmitionManager(this, port);
    this->eventsManager_= new ClientEventsManager(this);
}


Client::~Client(){
    delete this->screenManager_;
    delete this->transmitionManager_;
    delete this->eventsManager_;
}


bool Client::connectWithServer(){
    if (!this->transmitionManager_->connectWithServer(this->ipHost_)){
        this->connected_ = false;
        cout << "No se pudo conectar con el servidor con ip " + this->ipHost_ + " y puerto " + to_string(this->port_) << endl;
        connected_ = false;
        return false;
    }
    this->connected_ = true;

    this->transmitionManager_->run();
    this-> eventsManager_ -> RunProcessEventsThread();

    Logger::getInstance()->log(DEBUG, "Se creo el socket con exito. Se conecta el cliente con host " + this->ipHost_ + " y puerto " + to_string(this->port_));

    return true;
}


int Client::run(){
    
    setScreenSizes(1280,800);
    
    if (!this->screenManager_->initializeGraphics()){
        Logger::getInstance()->log(ERROR, "No se pudieron inicializar los gráficos, juego finalizado");
        return EXIT_FAILURE;
    };

    Logger::getInstance()->log(INFO, "Se inicializaron los graficos");

    if (!this->connectWithServer()){
        Logger::getInstance()->log(ERROR, "No se pudo conectar con el servidor, juego finalizado");
        return EXIT_FAILURE;
    }

    Logger::getInstance()->log(INFO, "Se estableció conexión con el servidor");
    cout << "Se estableció conexión con el servidor " << endl;

    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            Logger::getInstance()->log(INFO, "El usuario ha cerrado el menu de forma voluntaria");
            return EXIT_SUCCESS;
        }
    }

    bool logged = this->screenManager_-> viewLogin();

     if (!logged){
         Logger::getInstance()->log(INFO, "El usuario no ha podido loguearse,juego finalizado");
        disconnect();
         return EXIT_FAILURE;
    }

    int res = this->waitForPlayers();

    if(res==0){
        Logger::getInstance()->log(INFO, "El usuario cerró el juego,juego finalizado");
        return EXIT_SUCCESS;
    }
    
    else if (res<0){
        Logger::getInstance()->log(ERROR, "Ha ocurrido un problema con los gráficos al esperar jugadores,juego finalizado");
        return EXIT_FAILURE;
    }


    this->eventsManager_->RunDetectPlayerEventsThread();

    this->screenManager_->graphic();

    this->screenManager_->viewEndGameScreen();

    Logger::getInstance()->log(INFO, "El juego ha finalizado normalmente");
    
    return EXIT_SUCCESS;    
}

void Client::updateEntity(elementType_t type, position_t position){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un MapElement en Client");
    if(this->screenManager_){
        this->screenManager_->updateEntity(type, position);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido actualizar entidad,falta crear el objeto ScreenManager");
    }
}

void Client::setBackground(stage_t stage){
    Logger::getInstance()->log(DEBUG, "Se va a actualizar un background en Client");
    if(this->screenManager_){
        this->screenManager_->setBackground(stage);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido cargar el background,falta crear el objeto ScreenManager");
    } 
}


void Client::setImage(sceneScreen_t scene){
    Logger::getInstance()->log(DEBUG, "Se va a cargar imagen de fondo en Client");
    if(this->screenManager_){
        this->screenManager_->setImage(scene);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido cargar la imagen,falta crear el objeto ScreenManager");
    } 
}


void Client::setLoginResponse(responseStatus_t response){
    if(this->screenManager_){
        this->screenManager_->setLoginResponse(response);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido cargar la respuesta en el menu,falta crear el objeto ScreenManager");
    } 
}


size_t Client::getPort(){
    return this->port_;
}


string Client::getIpHost(){
    return this->ipHost_;
}


void Client::sendMessage(Message* message){
    this->transmitionManager_->sendMessage(message);
}

void Client::setScreenSizes(int Xsize, int Ysize){
    this->screenManager_->setScreenSizes(Xsize,Ysize);
}

bool Client::isConnected(){
    return this->connected_;
}

void Client::disconnect(){
    this->connected_ = false;
     Logger::getInstance()->log(DEBUG, "Se desconecta el cliente");
}

void Client::endGame(){
    this->disconnect();
}

int Client::waitForPlayers(){
    Logger::getInstance()->log(DEBUG, "Se esperaran jugadores en Client");
    return this->screenManager_->waitForPlayers();
}

void Client::initGame(int Xsize, int Ysize){
    this->screenManager_->stopWaiting();
    setScreenSizes(Xsize,Ysize);
}

void Client::processEvent(Event* event){
    this->eventsManager_->pushBackEvent(event);
}

void Client::updateScreen(){
    this->screenManager_->graphic();
}