#include "Server.h"

Server::Server(size_t port){
    this->port_ = port;
    this->maxPlayers = 0;
    this->connected_ = false;

    this->transmitionManager_ = new ServerTransmitionManager(this, port);
}

Server::~Server(){
    delete this->transmitionManager_;

    Logger::getInstance()->log(INFO, "Fin del juego");
}

//Pre: 
void Server::initializeServer() {
    if(!this->transmitionManager_->initialize()){
        this->connected_ = false;
        return;
    }

    this->connected_ = true;
    cout << "Se crea servidor escuchando el puerto " + to_string(this->port_) << endl;
}

bool Server::isConnected(){
    return this->connected_;
}

int Server::run(){
    this->initializeServer();

    if(!this->isConnected())
        return EXIT_FAILURE;

    if(!this->transmitionManager_->waitPlayers())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}