#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *serverOwn){
    // this->serverOwn_ = server;
    // this->socket_ = new Socket();
    // this->socket_->setPort(port);
    // pthread_mutex_init(&this->mutex_lastId_,NULL);
}

ServerTransmitionManager::~ServerTransmitionManager(){
    //pthread_mutex_destroy(&this->mutex_lastId_);
}


void ServerTransmitionManager::addUser(User* newUser){
    //ThreadsHandler::createThread(this->receivingCycle(), "Recibir jugador" + to_string(newUser->getUserId()));
    //ThreadsHandler::createThread(this->sendingCycle(), "Enviar jugador" + to_string(newUser->getUserId()));
}

void ServerTransmitionManager::receivingCycle() {
    
    //receiveMessage
}

status_t ServerTransmitionManager::sendingCycle() {
    // while(msj != "END_CONNECTION") {
    
    //
}