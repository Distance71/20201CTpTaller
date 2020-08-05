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
    Uint8 shoot;
    Uint8 music;
    Uint8 godMode;
    bool canShoot = true;

    const Uint8 *keystate;
    
 
    while (client->isConnected() && client->isLoggedIn()){

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
        shoot = keystate[SDL_SCANCODE_SPACE];
        music = keystate[SDL_SCANCODE_M];
        godMode = keystate[SDL_SCANCODE_X];

        orientation_t movementOrientation = NOT_MOVEMENT;

        Logger::getInstance()->log(DEBUG, "Se va a procesar un movimiento del jugador");


        if (up && !down && !right && !left){ 
            movementOrientation = UP;
        }
                
        else if(!up && down && !right && !left){
            movementOrientation = DOWN;
        }
                
        else if(!up && !down && right && !left){
            movementOrientation = FRONT;
        }
                
        else if(!up && !down && !right && left){
            movementOrientation = BACK;
        }

        else if(up && !down && right && !left){
            movementOrientation = FRONT_UP;
        }
                
        else if(up && !down && !right && left){
            movementOrientation = BACK_UP;
        }
                
        else if(!up && down && right && !left){ 
            movementOrientation = FRONT_DOWN;
        }
                
        else if(!up && down && !right && left){
            movementOrientation = BACK_DOWN;
        }

        if (movementOrientation != NOT_MOVEMENT){
            MessageUserMovement* message = new MessageUserMovement(movementOrientation);  
            client->sendMessage(message);
        }

        if (music)
        {
            Music::getInstance()->pause();  
        }

        if (godMode)
        {
            /* TODO */
        }  

        if (shoot && canShoot){
            client->sendMessage(new MessageUserShoot());
            canShoot = false;
        }

        // Si Space no esta presionada, le habilitamos poder dispara en proximo ciclo
        if (!shoot)
            canShoot = true;

        SDL_Delay(17);
        
    }   

    return nullptr;
}


void ClientEventsManager::RunDetectPlayerEventsThread(){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de detección de eventos del jugador");
    pthread_t detect_player_events_thread;
    pthread_create(&detect_player_events_thread, NULL, detectPlayerEvents, this);
}


/*static void* processEvents(void * arg){
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
}*/


void ClientEventsManager::RunProcessEventsThread(){
    Logger::getInstance()->log(DEBUG, "Se inicializa hilo de proceso de eventos");
     while(this->clientOwn_->isConnected()){
        Event* event = getEvent();
        if (event){
            event->setContext(this->clientOwn_);
            event->update();
            delete event;
        }
    }
}


Client* ClientEventsManager:: getClient(){
    return this->clientOwn_;
}

