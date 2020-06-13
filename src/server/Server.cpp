#include "Server.h"

Server::Server(size_t port){
    this->socket_ = new Socket(port);
    this->connected_ = false;
}

Server::~Server(){
    this->socket_->cerrar();
    //delete this->socket_;

    Logger::getInstance()->log(INFO, "Fin del juego");
}

//Pre: 
void Server::initializeServer() {

    if(!this->socket_->create()){
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

    size_t quantityPlayers = GameProvider::getQuantityPlayers();

    if(!this->socket_->escuchar(quantityPlayers)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->connected_ = true;
    Logger::getInstance()->log(DEBUG, "Se creo el socket con exito");
}

bool Server::isConnected(){
    return this->connected_;
}

int Server::run(){
    this->initializeServer();

    if(!this->isConnected())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}