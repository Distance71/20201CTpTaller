#include "Server.h"

Server::Server(size_t port){
    
    this->connected_ = false;
    this->socket_ = new Socket();
    this->socket_-> setPort(port);
    this->_initializeServer(port);
    
    this->usersManager_ = new UsersManager(this);
    this->eventsManager_ = new ServerEventsManager(this);

    this->game_ = new Game(this);
}


Server::~Server(){
    delete this->usersManager_;
    delete this->eventsManager_;
    delete this->game_;
    Logger::getInstance()->log(DEBUG, "Se han eliminado todos los recursos utilizados");
}


void Server::_initializeServer(size_t port) {
    
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

    size_t maxClients = GameProvider::getQuantityPlayers();

    if(!this->socket_->listenConnections(maxClients)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->connected_ = true;

    Logger::getInstance()->log(INFO, "Se inicializa el socket correctamente. Se pueden recibir clientes");
    cout << "Se crea servidor escuchando el puerto " + to_string(port) << endl;
}


bool Server::isConnected(){
    return this->connected_;
}

void Server::sendToUser(Id id,Event* event){
    this->usersManager_->sendEventToNotLoggedUser(id,event);
}

Socket* Server::getSocket(){
    return this->socket_;
}

void Server::processEvent(Event *event){
    this->eventsManager_->processEvent(event);
}


void Server::sendToAllUsers(Event* event){
    this->usersManager_->sendEventToAllLogged(event);
}

void Server::runGame(){

    Logger::getInstance()->log(INFO, "Juego iniciado");

    this->game_->run();
}

void Server::moveUser(string user, orientation_t orientation){
    this->game_->movePlayer(user, orientation);
}

responseStatus_t Server::loginRequest(Id id,string username,string password){
    this->usersManager_->loginRequest(id,username,password);
}

int Server::run(){

    if(!this->isConnected()) {
        Logger::getInstance()->log(ERROR, "El servidor no se pudo iniciar");
        return EXIT_FAILURE;
    }

    this->usersManager_-> runAcceptUsersThread();
    this->eventsManager_->RunProcessEventsThread();
    
    while (this->isConnected()){
        usleep(100000);
        if(this->usersManager_->isFullGame()){
            cout << "Se conectaron todos los jugadores, iniciará la partida"<< endl;
            Logger::getInstance()->log(INFO, "Se conectaron todos los jugadores, iniciará la partida");
            break;
        }
    }    
  
    this->runGame();

    Logger::getInstance()->log(INFO, "El Juego ha terminado");
    
    return EXIT_SUCCESS;
}

void Server::informDisconnection(string username){
    this->game_->informDisconnection(username);
}

void Server::informConnection(string username){
    this->game_->informConnection(username);
}

