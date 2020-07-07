#include "ClientEventsManager.h"
#include <stdio.h>

ClientEventsManager::ClientEventsManager(Client* client_){
    client = client_;
    events_queue = new BlockingQueue<Event*>();
}

ClientEventsManager::~ClientEventsManager(){}


void ClientEventsManager::pushBackEvent(Event* event){
    events_queue->push(event);
}

Event* ClientEventsManager::getEvent(){
    if (!events_queue->empty()){
        Event* event = *events_queue->pop();
        return event;
    }
    return nullptr;
}

Client* ClientEventsManager::getClient(){
    return client;
}

static void* processEvents(void * arg){
    ClientEventsManager* events_manager = (ClientEventsManager*) arg;
    Client * client = events_manager->getClient();
    while(client->isConnected()){
        Event* event = events_manager->getEvent();
        if (event){
            event->setContext(client);
            event->update();
            delete event;
        }
    }
}
static void * detectPlayerEvents(void* arg){
    Client* client = (Client*) arg;
    Uint8 up;
    Uint8 down;
    Uint8 right;
    Uint8 left;
    
    const Uint8 *keystate;
    
    while (client->isConnected()){
        keystate = SDL_GetKeyboardState(NULL);  
    
        up =  keystate[SDL_SCANCODE_UP];
        down = keystate[SDL_SCANCODE_DOWN];
        right =  keystate[SDL_SCANCODE_RIGHT];
        left = keystate[SDL_SCANCODE_LEFT];

        orientation_t movementOrientation = NOT_MOVEMENT;

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

        if (movementOrientation!=NOT_MOVEMENT){
            MessageUserMovement* message = new MessageUserMovement(movementOrientation);  
            client->sendMessage(message);
        }
    }
}

void ClientEventsManager::RunDetectPlayerEvents(){
    pthread_t detect_player_events_thread;
    pthread_create(&detect_player_events_thread,NULL,detectPlayerEvents,this->client);
}

void ClientEventsManager::processEventsRun(){
    pthread_t process_events_thread;
    pthread_create(&process_events_thread,NULL,processEvents,this);
}