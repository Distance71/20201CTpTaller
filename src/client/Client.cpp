#include "Client.h"

Client::Client(string ipHost,size_t port){
    this->connected_ = false;
    this->ipHost_ = ipHost;
    this->port_ = port;
    this->screenManager_= new ScreenManager(this);
    this->transmitionManager_ = new ClientTransmitionManager(this, port);
    this->eventsManager_= new ClientEventsManager(this);
    this-> loggedIn_ = false;
    this->serverDisconection_ = false;
    this->endGame_ = false;
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

    this->screenManager_-> viewLogin();

    this-> eventsManager_ -> RunProcessEventsThread();

    Logger::getInstance()->log(INFO, "El juego ha finalizado normalmente");
    
    if (this->serverDisconection_ || this->endGame_)
        usleep(3000000);
    
    
    return EXIT_SUCCESS;    
}



void Client::updateEntity(elementType_t type, position_t position){
    this->screenManager_->updateEntity(type, position); 
}

void Client::updateBackgroundLayer(layer_t layer, stage_t stage, int step){
    this->screenManager_->updateBackgroundLayer(layer,stage,step);
}

void Client::setImage(sceneScreen_t scene){
    this->screenManager_->setImage(scene);
}


void Client::setLoginResponse(responseStatus_t response){
    this->screenManager_->setLoginResponse(response);
}


size_t Client::getPort(){
    return this->port_;
}


string Client::getIpHost(){
    return this->ipHost_;
}

bool Client::isLoggedIn(){
    return this->loggedIn_;
}

void Client::setLoggedInStatus(){
    this->loggedIn_ = true;
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
    this->endGame_ = true;
    this->screenManager_->setImage(END_GAME_ANIMATION);
    this->disconnect();
}

void Client::gameOver(){
    this->endGame_ = true;
    this->screenManager_->setImage(GAME_OVER_ANIMATION);
    this->disconnect();
}

void Client::processEvent(Event* event){
    this->eventsManager_->pushBackEvent(event);
}

void Client::ServerDisconnection(){
    this->serverDisconection_ = true;
    this->disconnect();
    usleep(100000);
    this->screenManager_->ServerDisconnection();
    usleep(500000);
    
}

void Client::runDetectEventThread(){
    this->eventsManager_-> RunDetectPlayerEventsThread();
}