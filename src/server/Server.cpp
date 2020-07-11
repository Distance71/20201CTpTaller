#include "Server.h"
#include <stdio.h>

Server::Server(size_t port){
    this->port_ = port;
    
    this->socket_ = new Socket();
    this->socket_->setPort(port);
    this->_initializeServer();
    this->transmitionManager_ = new ServerTransmitionManager(this);
    this->usersManager_ = new UsersManager(this);
    this->eventsManager_ = new ServerEventsManager(this);
    
    // this->transmitionManager_->run();
    // this->usersManager_->run();
    // this->eventsManager_->run();
}

Server::~Server(){
    delete this->usersManager_;
    delete this->transmitionManager_;
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

void Server::waitPlayers(){
    cout << "Esperando jugadores..." << endl;

    while (!this->usersManager_->isFullGame() && this->isConnected()){
        
        size_t newUserId = this->usersManager_->acceptUnloggedUser();
        
        if (newUserId == 0){            
            // error ya informado
        }
        else{
            if(this->usersManager_->isFullGame()) {
                Logger::getInstance()->log(DEBUG, "Se ha querido conectar usuario con el juego lleno");
            }
            cout << "Se agrega un cliente. " << endl;
            Logger::getInstance()->log(INFO, "Se ha conectado un usuario nuevo");
        }
    }

    Logger::getInstance()->log(DEBUG, "Se ha terminado de esperar jugadores");    
}

Socket* Server::getSocket(){
    return this->socket_;
}

// BlockingQueue<Message *>* Server::getEventsToProcess(){
//     return transmitionManager_->getMessagesToProcess();
// }

void Server::addPlayer(User *newUser){
    if(!newUser || usersManager_->isFullGame()) {
        Logger::getInstance()->log(ERROR, "Se ha querido iniciar un usuario en el servidor sin contenido");
        return;
    }

    this->transmitionManager_->addUser(newUser);

    // pthread_mutex_lock(&this->mutex_players_);

    // if (this->isFull()){
    //     pthread_mutex_unlock(&this->mutex_players_);
    //     return false;
    // }   
    
    // cout << "El cliente " + to_string(idPlayer) + " se agrega a la partida" << endl;
    // this->players_[idPlayer] = onePlayer;
    // pthread_mutex_unlock(&this->mutex_players_);
    // return true;
}

int Server::run(){

    if(!this->isConnected()) {
        Logger::getInstance()->log(ERROR, "El servidor no se pudo iniciar");
        return EXIT_FAILURE;
    }
    this->waitPlayers();

    this->runGame();

    Logger::getInstance()->log(INFO, "El Juego ha terminado");
    return EXIT_SUCCESS;
}

void Server::runGame(){

    Logger::getInstance()->log(INFO, "Juego iniciado");

    Game *game = new Game();

    game->run();
}