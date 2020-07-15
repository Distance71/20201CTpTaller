#include "Server.h"
#include <stdio.h>

Server::Server(size_t port){
    this->port_ = port;
    this->socket_ = new Socket();
    this->socket_->setPort(port);
    this->_initializeServer();
    this->usersManager_ = new UsersManager(this);
    this->eventsManager_ = new ServerEventsManager(this);
}

Server::~Server(){
    delete this->usersManager_;
    delete this->eventsManager_;
    Logger::getInstance()->log(DEBUG, "Se han eliminado todos los recursos utilizados");
}

void Server::_initializeServer() {
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

    if (!this->socket_->link()) {
        string errorMessage = "No se pudo asignar una direccion al socket del server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    size_t maxUsers = GameProvider::getQuantityPlayers();

    if(!this->socket_->listenConnections(maxUsers)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->connected_ = true;

    Logger::getInstance()->log(INFO, "Se inicializa el socket correctamente. Se pueden recibir clientes");
    cout << "Se crea servidor escuchando el puerto " + to_string(this->port_) << endl;
}

bool Server::isConnected(){
    return this->connected_;
}

Socket* Server::getSocket(){
    return this->socket_;
}



int Server::run(){

    if(!this->isConnected()) {
        Logger::getInstance()->log(ERROR, "El servidor no se pudo iniciar");
        return EXIT_FAILURE;
    }

    this->usersManager_-> runAcceptUsersThread();
    
    while (this->isConnected()){
        if(this->usersManager_->isFullGame()){
            cout <<"Se conectaron todos los jugadores, iniciará la partida"<< endl;
            break;
        }
    }     

      char pathElement1[100];
        strcpy(pathElement1, "assets/Enemies/enemigo1.png");
        position_t position1;
        spriteSize_t spriteSize1;
        spriteSize1.width = 100;
        spriteSize1.height = 100;

  
    this->runGame();

    Logger::getInstance()->log(INFO, "El Juego ha terminado");
    
    return EXIT_SUCCESS;
}


void Server::processEvent(Event *event){
    this->eventsManager_->processEvent(event);
}

void Server::runGame(){

    Logger::getInstance()->log(INFO, "Juego iniciado");

    this->game = new Game(this);

    this->game->run();
}

void Server::sendToAllUsers(Event* event){
    this->usersManager_->sendToAll(event);
}

void Server::moveUser(Id idUser, orientation_t orientation){
    this->game->movePlayer(idUser, orientation);
}
