#include "UsersManager.h"
#include <stdio.h>
UsersManager::UsersManager(Server *serverOwn){
    this->serverOwn_ = serverOwn;
    this->maxUsers_ = GameProvider::getQuantityPlayers();
    this->socket_ = this->serverOwn_->getSocket();
    this->lastId_ = 0;
    this->loggedUsers_ = 0;
}

UsersManager::~UsersManager(){
}


bool UsersManager::isFullGame(){
    return this->loggedUsers_ == 2;
}


void UsersManager::acceptUser(){

    Id idUser = this-> lastId_;

    int newClientDescriptor = this->socket_->acceptClient();
    
    if (newClientDescriptor < 0){
        Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        return;
    }

    Socket *socketNewUser = new Socket(newClientDescriptor);
    
    User* newUser = new User(socketNewUser,this);

    newUser->setConnection();

    newUser->runSendingMessagesThread();
    newUser->runReceivingMessagesThread();

    this->users_.emplace(idUser,newUser);
    
    this->lastId_ ++;

    this->loggedUsers_ ++;

    Logger::getInstance()->log(INFO, "Se ha conectado un usuario nuevo");

}

Server* UsersManager::getServer(){
    return this-> serverOwn_;
}


static void * acceptUsers (void* arg){
    
    UsersManager* manager = (UsersManager* ) arg;
    
    Server* server = manager->getServer();
    
    cout << "Esperando jugadores..." << endl;
    
    while (server->isConnected()){
       
        manager->acceptUser();
        
    }

    Logger::getInstance()->log(DEBUG, "Se ha detenido el hilo de detección");

}


void UsersManager::runAcceptUsersThread(){
    pthread_t acceptUsersThread;
    pthread_create(&acceptUsersThread,NULL,acceptUsers,this);
 }


bool UsersManager::isConnectedUser(Id id){
    return this->users_[id]->isConnected();
}


void UsersManager::disconnectUser(Id id){
     this->users_[id]->setDisconnection();
 }

void UsersManager::setConnection(Id id){
     this->users_[id]->setConnection();
 }


void UsersManager::loginUser(Id id){
    this->users_[id]->setLoggedIn();
    this->loggedUsers_ ++;
}


void UsersManager::sendEventToUser(Id id, Event* event){
    this->users_[id]->sendEvent(event);
}


void UsersManager::processEvent(Event* event){
    this->serverOwn_->processEvent(event);
}

void UsersManager::sendToAll(Event* event){
    for (auto user : this->users_){
        sendEventToUser(user.first,event);
    }
}