#include "Client.h"

Client::Client(string ipHost,size_t port){

    this->connected_ = false;
    this->ipHost_ = ipHost;
    this->port_ = port;
    this->screenManager_= nullptr;
    this->transmitionManager_ = nullptr;
    this->eventsManager_= nullptr;
}


Client::~Client(){
    delete this->screenManager_;
    delete this->transmitionManager_;
    delete this->eventsManager_;
}


bool Client::connectWithServer(){
    
    this->transmitionManager_ = new ClientTransmitionManager(this);
    
    if (!this->transmitionManager_->connectWithServer()){
        this->connected_ = false;
        cout << "No se pudo conectar con el servidor con ip " + this->ipHost_ + " y puerto " + to_string(this->port_) << endl;
        delete this->transmitionManager_;
        this->transmitionManager_ = nullptr;
        connected_ = false;
        return false;
    }
    
    transmitionManager_->runThreads();

    eventsManager_ = new ClientEventsManager(this);

    eventsManager_ -> RunProcessEventsThread();

    this->connected_ = true;

    Logger::getInstance()->log(DEBUG, "Se creo el socket con exito. Se conecta el cliente con host " + this->ipHost_ + " y puerto " + to_string(this->port_));

    return true;
}


bool Client::isConnected(){
    return this->connected_;
}


int Client::run(){
    
    if (!this->connectWithServer()){
        Logger::getInstance()->log(ERROR, "No se pudo conectar con el servidor, juego finalizado");
        return EXIT_FAILURE;
    }

    Logger::getInstance()->log(INFO, "Se estableció conexión con el servidor");
    cout << "Se estableció conexión con el servidor " << endl;

    this->screenManager_= new ScreenManager(this);
    
    // esperar por seteo del tamaño de pantalla
    
    if (!this->screenManager_->initializeGraphics()){
        Logger::getInstance()->log(ERROR, "No se pudieron inicializar los gráficos, juego finalizado");
        return EXIT_FAILURE;
    };

    bool logged = this->screenManager_-> viewLogin();

    if (!logged){
        Logger::getInstance()->log(INFO, "El ususario no ha podido loguearse,juego finalizado");
        return EXIT_FAILURE;
    }

    this->eventsManager_->RunDetectPlayerEventsThread();
    this->screenManager_->initGameGraphics();
    return EXIT_SUCCESS;    
}


void Client::createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation){
    if(this->screenManager_){
        this->screenManager_->createEntity(id,source,sizeX,sizeY,posX,posY,orientation);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido crear entidad,falta crear el objeto ScreenManager");
    }
}


void Client::updateEntity(IdElement id, int posX, int posY, orientation_t orientation){
    if(this->screenManager_){
        this->screenManager_->updateEntity(id,posX,posY,orientation);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido actualizar entidad,falta crear el objeto ScreenManager");
    }
}


void Client::deadEntity(IdElement id){
    if(this->screenManager_){
        this->screenManager_->deadEntity(id);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido eliminar entidad,falta crear el objeto ScreenManager");
    }
}


void Client::setBackground(stageSource_t background){
    if(this->screenManager_){
        this->screenManager_->setBackground(background);
    }
    else{
         Logger::getInstance()->log(DEBUG, "No se ha podido cargar el background,falta crear el objeto ScreenManager");
    } 
}


void Client::setImage(const string &source){
    if(this->screenManager_){
        this->screenManager_->setImage(source);
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