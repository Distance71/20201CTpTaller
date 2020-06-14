#include "Server.h"

Server::Server(size_t port){
    this->port_ = port;
    this->maxPlayers = 0;
    this->connected_ = false;

    this->transmitionManager_ = new ServerTransmitionManager(this, port);
}

Server::~Server(){
    delete this->transmitionManager_;

    //this->socket_->cerrar();
    //delete this->socket_;

    Logger::getInstance()->log(INFO, "Fin del juego");
}

//Pre: 
void Server::initializeServer() {

    /*if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket para recibir clientes en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    if(!this->socket_->setOption()){
        string errorMessage = "No se pudieron setear las opciones del socket en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    if (!this->socket_->enlazar()) {
        string errorMessage = "No se pudo asignar una direccion al socket del server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->maxPlayers = GameProvider::getQuantityPlayers();

    if(!this->socket_->escuchar(this->maxPlayers)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->connected_ = true;
    Logger::getInstance()->log(INFO, "Se creo el socket con exito");*/

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