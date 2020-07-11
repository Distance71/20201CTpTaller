#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server){
    this->serverOwn_ = server;
    //receivedMessagesQueue_ = new BlockingQueue <Message*>();
}

ServerTransmitionManager::~ServerTransmitionManager(){
    //delete this->receivedMessagesQueue_;
}

void ServerTransmitionManager::addUser(User* user){
    this->createReceivingCycle(user);
    //this->createSendingCycle(user);
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


    //Not handled
    if(pthreadCreateStatus != 0) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario" + to_string(user->getId());
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision receptor.");
}

void* ServerTransmitionManager::receivingCycle(User* user){
    Logger::getInstance()->log(DEBUG, "Se va iniciar el ciclo del receptor transmitionManager");
    
    if(!user || !this->serverOwn_)
        cout << "algo esta mal" << endl;
        
    while (user->isConnected() && this->serverOwn_->isConnected()) {
        Logger::getInstance()->log(DEBUG, "Se va a recibir un evento en transmitionManager");
        Event *event = user->receiveMessage();
        if(!event){
            mtxErrno.lock();
            if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
                Logger::getInstance()->log(DEBUG, "Se detecta desconexión del cliente."+ to_string(user->getId()));
                user->setDisconnection();
                return nullptr;
            }
            mtxErrno.unlock();
            Logger::getInstance()->log(ERROR, "Se ha recibido un evento invalido. Se cerrará la conexión con el cliente");
            return nullptr;
        }
        Logger::getInstance()->log(DEBUG, "Se recibio un evento");
        cout << "se recibio un mensaje" << endl;
        //receivedMessagesQueue_->push(message);        
    }
    
    Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente " + to_string(user->getId()));
    return nullptr;
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