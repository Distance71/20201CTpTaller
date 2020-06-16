#include "UsersManager.h"

UsersManager::UsersManager(IdPlayer idPlayer, Socket *socket, Server *server){
    this->id_ = idPlayer;
    this->socket_ = socket;
    this->serverOwn_ = server;
}

UsersManager::~UsersManager(){}

void UsersManager::setIdPlayer(IdPlayer idPlayer){
    this->id_ = idPlayer;
}

IdPlayer UsersManager::getIdPlayer(){
    return this->id_;
}

void UsersManager::setSocket(Socket *socket){
    this->socket_ = socket;
}
