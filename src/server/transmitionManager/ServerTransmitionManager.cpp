#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server){
    this->serverOwn_ = server;
    this->receivedMessagesQueue_ = new BlockingQueue();
}

ServerTransmitionManager::~ServerTransmitionManager(){
    //pthread_mutex_destroy(&this->mutex_lastId_);
    delete this->receivedMessagesQueue_;
}

void ServerTransmitionManager::addUser(User* user){
    this->createReceivingCycle(user);
    this->createSendingCycle(user);
}

void ServerTransmitionManager::createReceivingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;
    
    args.handler = (void *) this;
    args.params = user; 

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args) -> void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        handler->receivingCycle(user);
        return nullptr;
    }, (void *) &args);

    if(!pthreadCreateStatus) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario".append(to_string(user->getId()));
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision.");
}

void* ServerTransmitionManager::receivingCycle(User* user){
    
    while (user->isConnected() && this->serverOwn_->isConnected()) {
        
        Message *message = user->receiveMessage();
        if(!message){

            //Add mutex to errno
            if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
                Logger::getInstance()->log(ERROR, "Se detecta desconexión involuntaria del cliente.".append(to_string(user->getId())));
                user->setDisconnection();
                return nullptr;
            }
        }

        receivedMessagesQueue_->push(message);        
    }
    
    Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente".append(to_string(user->getId())));
}

BlockingQueue* ServerTransmitionManager::getMessagesToProcess(){
    return this->receivedMessagesQueue_;
}

void ServerTransmitionManager::createSendingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;
    
    args.handler = (void *) this;
    args.params = user; 

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args) -> void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        handler->sendingCycle(user);
        return nullptr;
    }, (void *) &args);

    if(!pthreadCreateStatus) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario".append(to_string(user->getId()));
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision.");
}



void ServerTransmitionManager::sendingCycle(User* user) {
    
    while(user->isConnected() && this->serverOwn_->isConnected()){
        if(messagesQueue.isEmpty())
            continue;
        
        Message* message = messagesQueues_[user->getId()].pop();

        user->sendMessage(message);
    }
}