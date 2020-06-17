#include "Server.h"

Server::Server(size_t port){
    this->port_ = port;
    this->maxPlayers_ = GameProvider::getQuantityPlayers();;
    this->connected_ = false;

    this->transmitionManager_ = new ServerTransmitionManager(this, port);
    pthread_mutex_init(&this->mutex_players_,NULL);
}

Server::~Server(){
    delete this->transmitionManager_;
    pthread_mutex_destroy(&this->mutex_players_);

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

bool Server::addPlayer(IdPlayer idPlayer, UsersManager *onePlayer){

    pthread_mutex_lock(&this->mutex_players_);

    if (this->isFull()){
        pthread_mutex_unlock(&this->mutex_players_);
        return false;
    }   
    
    cout << "El cliente " + to_string(idPlayer) + " se agrega a la partida" << endl;
    this->players_[idPlayer] = onePlayer;
    pthread_mutex_unlock(&this->mutex_players_);
    return true;
}

bool Server::isFull(){
    return (this->players_.size() >= this->maxPlayers_);
}

int Server::run(){
    this->initializeServer();

    if(!this->isConnected())
        return EXIT_FAILURE;

    if(!this->transmitionManager_->waitPlayers())
        return EXIT_FAILURE;

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