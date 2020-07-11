#include "ClientEventsManager.h"
#include <stdio.h>

ClientEventsManager::ClientEventsManager(Client* client){
    this->clientOwn_ = client;
    this->eventsQueue_ = new BlockingQueue<Event*>();
}


ClientEventsManager::~ClientEventsManager(){
    //delete this->eventsQueue_; esto da violación de segmento
}


void ClientEventsManager::pushBackEvent(Event* event){
    this->eventsQueue_->push(event);
}


Event* ClientEventsManager::getEvent(){
    if (!eventsQueue_->empty()){
        Event* event = *eventsQueue_->pop();
        return event;
    }
    return nullptr;
}


static void * detectPlayerEvents(void* arg){
    ClientEventsManager* eventsManager = (ClientEventsManager*) arg;
    Client* client = eventsManager->getClient();
    Uint8 up;
    Uint8 down;
    Uint8 right;
    Uint8 left;
    
    const Uint8 *keystate;
    
    while (client->isConnected()){

        SDL_Event e;

        while (SDL_PollEvent(&e)){
            
            GameProvider::setLastEvent(e);
            
            if (e.type == SDL_QUIT){
                Logger::getInstance()->log(INFO, "El usuario ha cerrado el menu de forma voluntaria");
                client->disconnect();
            }
        }
            
        keystate = SDL_GetKeyboardState(NULL);  
    
        up =  keystate[SDL_SCANCODE_UP];
        down = keystate[SDL_SCANCODE_DOWN];
        right =  keystate[SDL_SCANCODE_RIGHT];
        left = keystate[SDL_SCANCODE_LEFT];

        orientation_t movementOrientation = NOT_MOVEMENT;

        if (up && !down && !right && !left){ 
            movementOrientation = UP;
            printf("arriba\n");
        }
        
        else if(!up && down && !right && !left){
            movementOrientation = DOWN;
            printf("abajo\n");
        }
        
        else if(!up && !down && right && !left){
            movementOrientation = FRONT;
            printf("derecha\n");
        }
        
        else if(!up && !down && !right && left){
            printf("izquierda\n");
            movementOrientation = BACK;
        }

        else if(up && !down && right && !left){
            printf("DERECHA ARRIBA\n");
            movementOrientation = FRONT_UP;
        }
        
        else if(up && !down && !right && left){ 
            printf("IZQUIERDA ARRIBA\n");
            movementOrientation = BACK_UP;
        }
        
        else if(!up && down && right && !left){ 
            printf("DERECHA ABAJO\n");
            movementOrientation = FRONT_DOWN;
        }
        
        else if(!up && down && !right && left){
            movementOrientation = BACK_DOWN;
            printf("IZQUIERDA ABAJO\n");
        }

        if (movementOrientation!=NOT_MOVEMENT){
            MessageUserMovement* message = new MessageUserMovement(movementOrientation);  
            client->sendMessage(message);
        }

        SDL_Delay(100);
    }

    return nullptr;
}


void ClientEventsManager::RunDetectPlayerEventsThread(){
    this->stop_=false;
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de detección de eventos del jugador");
    pthread_t detect_player_events_thread;
    pthread_create(&detect_player_events_thread,NULL,detectPlayerEvents,this);
}


static void* processEvents(void * arg){
    ClientEventsManager* eventsManager = (ClientEventsManager*) arg;
    Client * client = eventsManager->getClient();
    while(client->isConnected()){
        Event* event = eventsManager->getEvent();
        if (event){
            event->setContext(client);
            event->update();
            delete event;
        }
    }
    return nullptr;
}


void ClientEventsManager::RunProcessEventsThread(){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de proceso de eventos");
    pthread_t process_events_thread;
    pthread_create(&process_events_thread,NULL,processEvents,this);
}


Client* ClientEventsManager:: getClient(){
    return this->clientOwn_;
}
