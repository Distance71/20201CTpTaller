#include "ServerEventsManager.h"

ServerEventsManager::ServerEventsManager(Server *server){
    this->serverOwn_ = server;
    this->receivedMessagesQueue_ = new BlockingQueue();
}

ServerEventsManager::~ServerEventsManager(){

}

void ServerEventsManager::processingCycle() {
    pthread_t thread;

    argsThread_t args;
    
    args.handler = (void *) this;

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args) -> void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerEventsManager *) arguments->handler;

        handler->processingCycle();
        return nullptr;
    }, (void *) &args);

    if(!pthreadCreateStatus) {
        string errorMessage = "No se pudo crear el hilo para manejar el procesamiento de eventos";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de procesamiento de eventos.");
}

void* ServerEventsManager::processingCycle(){

    events = serverOwn_->getEventsToProcess();
    
    while (this->serverOwn_->isConnected()) {
        
        Event *event = events.pop();
        event->execute();
        Logger::getInstance()->log(DEBUG, "Se ha cargado un evento");
    }
    
}

getMessagesToProcess