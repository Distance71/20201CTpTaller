#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server){
    this->serverOwn_ = server;
    //cout << this << endl;
    //receivedMessagesQueue_ = new BlockingQueue <Message*>();
}

ServerTransmitionManager::~ServerTransmitionManager(){
    //pthread_mutex_destroy(&this->mutex_lastId_);
    //delete this->receivedMessagesQueue_;
}

void ServerTransmitionManager::addUser(User* user){
    //this->createReceivingCycle(user);
    this->createSendingCycle(user);
}

void ServerTransmitionManager::createReceivingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;
    
    args.handler = (void *) this;
    args.params = user; 

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args)->void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        return handler->receivingCycle(user);
    }, (void *) &args);

    if(pthreadCreateStatus != 0) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario" + to_string(user->getId());
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision receptor.");
}

void* ServerTransmitionManager::receivingCycle(User* user){
    
    while (user->isConnected() && this->serverOwn_->isConnected()) {
        
        Event *event = user->receiveMessage();
        if(!event){
            //Add mutex to errno
            if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
                Logger::getInstance()->log(ERROR, "Se detecta desconexión involuntaria del cliente."+ to_string(user->getId()));
                user->setDisconnection();
                return nullptr;
            }
        }
        if(event != nullptr)
            cout << "se recibio un mensaje" << endl;
        //receivedMessagesQueue_->push(message);        
    }
    
    Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente " + to_string(user->getId()));
}



// BlockingQueue<Message *>* ServerTransmitionManager::getMessagesToProcess(){
//     return this->receivedMessagesQueue_;
// }

void ServerTransmitionManager::createSendingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;

    args.handler = (void *) this;
    args.params = user;

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args) -> void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        return handler->sendingCycle(user);
    }, (void *) &args);

    if(pthreadCreateStatus != 0) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario" + to_string(user->getId());
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision emisor.");
}



void* ServerTransmitionManager::sendingCycle(User* user) {
    
    while(user->isConnected() && this->serverOwn_->isConnected()){
    //     //if(messagesQueues_[user->getId()]->empty())
    //     //    continue;
        
    //     //Message* message = (Message*) messagesQueues_[user->getId()]->pop();
        responseStatus_t responseStatus = ERROR_FULL_GAME;
    //     OK,
    // ERROR_CONNECTION,
    // ERROR_MESSAGE,
    // ERROR_FULL_GAME,
    // ERROR_WRONG_CREDENTIALS,
        Event* event = new EventResponseLoginPlayer(responseStatus);

        response_t response = user->sendMessage(event);
        //response = user->sendMessage(event);

        if(response.ok)
            cout << "Se mando ok" << endl;
    //     return nullptr;
        //return nullptr;
    }
    return nullptr;
}