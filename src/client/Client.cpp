#include "Client.h"

Client::Client(string ipAddress, size_t port){
    this->name_ = "";
    this->ipHost_ = ipAddress;
    this->port_ = port;
    this->eventsManager_= new ClientEventsManager(this);

    GameProvider::setWidth(1280);
    GameProvider::setHeight(800);
    this->gameScreen_ = new GameScreen(this);
    this->transmitionManager_ = new ClientTransmitionManager(this, port);
}

Client::~Client(){
    delete this->gameScreen_;
    delete this->transmitionManager_;
}

void Client::initializeClient(){
    if (!this->transmitionManager_->connectWithServer(this->ipHost_)){
        this->connected_ = false;
        cout << "No se pudo conectar con el servidor con ip " + this->ipHost_ + " y puerto " + to_string(this->port_) << endl;
        return;
    }
    
    this->connected_ = true;
    transmitionManager_->run();
    eventsManager_->processEventsRun();
    
    Logger::getInstance()->log(INFO, "Se creo el socket con exito. Se conecta el cliente con host " + this->ipHost_ + " y puerto " + to_string(this->port_));
}

int Client::run(){
    this->initializeClient();
    if (!this->isConnected())
        return EXIT_FAILURE;
    
    cout << "Se conecta con el servidor " << endl;
    this-> gameScreen_->viewLogin();
    eventsManager_->RunDetectPlayerEvents();
    gameScreen_->runGraphics();
    
    return EXIT_SUCCESS;    
}

bool Client::isConnected(){
    return this->connected_;
}

void Client::disconnect(){
    this->connected_ = false;

    // Cerrar conexiones, socket, logger situacion...
}

void Client::setName(string oneName){
    this->name_ = oneName;
}

string Client::getName(){
    return this->name_;
}

GameScreen *Client::getGameScreen(){
    return this->gameScreen_;
};

ClientTransmitionManager *Client::getTransmitionManager(){
    return this->transmitionManager_;
}

ClientEventsManager* Client::getEventsManager(){
    return this->eventsManager_;
}

void Client::sendMessage(Message* message){
    transmitionManager_->sendMessage(message);
}