#include "ClientEventsManager.h"
#include <stdio.h>
#include <errno.h>
#include <thread>

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
        Event* event = eventsQueue_->pop();
        return event;
    }
    return nullptr;
}


static void * detectPlayerEvents(void* arg){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de detección de eventos del jugador internamente");
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
                Logger::getInstance()->log(INFO, "El usuario ha cerrado el juego de forma voluntaria");
                client->disconnect();
            }
        }
            
        keystate = SDL_GetKeyboardState(NULL);  
    
        up =  keystate[SDL_SCANCODE_UP];
        down = keystate[SDL_SCANCODE_DOWN];
        right =  keystate[SDL_SCANCODE_RIGHT];
        left = keystate[SDL_SCANCODE_LEFT];

        orientation_t movementOrientation = NOT_MOVEMENT;

        Logger::getInstance()->log(DEBUG, "Se va a procesar un movimiento del jugador");


        if (up && !down && !right && !left){ 
            movementOrientation = UP;
            cout << "ARRIBA" << endl;
        }
        
        else if(!up && down && !right && !left){
            movementOrientation = DOWN;
            cout << "ABAJO" << endl;
        }
        
        else if(!up && !down && right && !left){
            movementOrientation = FRONT;
            cout << "DERECHA" << endl;
        }
        
        else if(!up && !down && !right && left){
            movementOrientation = BACK;
            cout << "IZQUIERDA" << endl;
        }

        else if(up && !down && right && !left){
            cout << "DERECHA ARRIBA" << endl;
            movementOrientation = FRONT_UP;
        }
        
        else if(up && !down && !right && left){
            cout << "IZQUIERDA ARRIBA" << endl; 
            movementOrientation = BACK_UP;
        }
        
        else if(!up && down && right && !left){ 
            cout << "DERECHA ABAJO" << endl;
            movementOrientation = FRONT_DOWN;
        }
        
        else if(!up && down && !right && left){
            cout << "IZQUIERDA ABAJO" << endl;
            movementOrientation = BACK_DOWN;
        }

        if (movementOrientation != NOT_MOVEMENT){
            MessageUserMovement* message = new MessageUserMovement(movementOrientation);  
            client->sendMessage(message);
        }

        SDL_Delay(16);
    }

    return nullptr;
}


void ClientEventsManager::RunDetectPlayerEventsThread(){
    //this->stop_ = false;
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de detección de eventos del jugador");
    pthread_t detect_player_events_thread;
    pthread_create(&detect_player_events_thread, NULL, detectPlayerEvents, this);
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
