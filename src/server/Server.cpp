#include "Server.h"
#include <stdio.h>

Server::Server(size_t port){
    this->port_ = port;
    this->usersManager_ = new UsersManager(this);
    this->socket_ = new Socket();
    this->socket_->setPort(port);
    this->transmitionManager_ = new ServerTransmitionManager(this);
    this->_initializeServer();
}

Server::~Server(){
    delete this->usersManager_;
    delete this->transmitionManager_;
    Logger::getInstance()->log(INFO, "Fin del juego");
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

    //Se compara con el Server porque ServerTransmitionManager puede tener mas usuarios de la cantidad del juego
    //porque el Socket hace el accept antes de que del logeo y demas
    while (!this->usersManager_->isFullGame() && this->isConnected()){
        
        size_t newUserId = this->usersManager_->acceptUnloggedUser();

        if (newUserId == 0){
            bool isFullGame = this->usersManager_->isFullGame();
            if(isFullGame) {
                //Some debug log
                break;
            }
            //error de accept ya fue informado en acceptUnloggedUser <borrar esta linea>*/
        }
        else{
          //cout << "Se agrega el cliente " << newUserId << endl;
        }
        //Here should handle validation
    }

};

Socket* Server::getSocket(){
    return this->socket_;
}

BlockingQueue<Message *>* Server::getEventsToProcess(){
    return transmitionManager_->getMessagesToProcess();
}

void Server::addPlayer(User *newUser){
    if(!newUser || usersManager_->isFullGame()) {
        //Handle error
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
        //Handle error
        return EXIT_FAILURE;
    }
        

    this->waitPlayers();

    //Here goes gameRun that generates events for events manager

    /*while (this->isConnected()){
        string strQuit;
        cin >> strQuit;
        boost::to_upper(strQuit);
        if (strQuit == "QUIT"){
            this->connected_ = false;
            cout << "Has cerrado la partida." << endl;
        } else {
            cout << "Comando no válido." << endl;
        }
    }*/

    return EXIT_SUCCESS;
}

void Server::runGame(){

}