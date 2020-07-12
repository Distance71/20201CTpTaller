#include "ServerEventsManager.h"

ServerEventsManager::ServerEventsManager(Server *server){
    this->serverOwn_ = server;
    this->eventsQueue_ = new BlockingQueue<Event*>();
}

ServerEventsManager::~ServerEventsManager(){
    delete this->eventsQueue_;
}

void ServerEventsManager::process(Event *event) {
     this->eventsQueue_->push(event);
     Logger::getInstance()->log(DEBUG, "Se ha cargado un evento");
}

Event* ServerEventsManager::getEvent(){
    if (!eventsQueue_->empty()){
        Event* event = eventsQueue_->pop();
        return event;
    }
    return nullptr;
}


// chequear ...
static void* processEvents(void * arg){
    ServerEventsManager* eventsManager = (ServerEventsManager*) arg;
    Server * server = eventsManager->getServer();
    while(server->isConnected()){
        Event* event = eventsManager->getEvent();
        if (event){
            event->setContext(server);
            event->update();
            delete event;
        }
    }
    return nullptr;
}

void ServerEventsManager::RunProcessEventsThread(){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de proceso de eventos");
    pthread_t process_events_thread;
    pthread_create(&process_events_thread,NULL,processEvents,this);
}

Server* ServerEventsManager::getServer(){
    return this->serverOwn_;
}

void ServerEventsManager::processingCycle() {
        //TODO: A REVISAR
    pthread_t thread;

    argsThread_t args;
    
    /*args.handler = (void *) this;

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

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de procesamiento de eventos.");*/
}