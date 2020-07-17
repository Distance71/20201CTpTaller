#include "ServerEventsManager.h"

ServerEventsManager::ServerEventsManager(Server *server){
    this->serverOwn_ = server;
    this->eventsQueue_ = new BlockingQueue<Event*>();
}


ServerEventsManager::~ServerEventsManager(){
    delete this->eventsQueue_;
}


void ServerEventsManager::processEvent(Event *event) {
    this->eventsQueue_->push(event);
}


Server* ServerEventsManager::getServer(){
    return this->serverOwn_;
}


Event* ServerEventsManager::getEvent(){
    if (!eventsQueue_->empty()){
        Event* event = eventsQueue_->pop();
        return event;
    }
    return NULL;
}


static void* processEvents(void * arg){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de proceso de eventos");
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

    Logger::getInstance()->log(DEBUG, "Finaliza el hilo de proceso de eventos");

    return nullptr;
}


void ServerEventsManager::RunProcessEventsThread(){
    pthread_t process_events_thread;
    pthread_create(&process_events_thread,NULL,processEvents,this);
}