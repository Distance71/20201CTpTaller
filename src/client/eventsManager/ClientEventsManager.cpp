#include "ClientEventsManager.h"

ClientEventsManager::ClientEventsManager(Client* client_){
    client = client_;
}

ClientEventsManager::~ClientEventsManager(){}



void ClientEventsManager::processEvents(){
    while(client->isConnected()){
        Event* event = getEvent();
        /*if (event){
            event->update();
        }*/
    }
}


void ClientEventsManager::pushBackEvent(Event* event){
    events_queue.push_back(event);
}

Event* ClientEventsManager::getEvent(){
    if (!events_queue.empty()){
        Event* event = events_queue.front();
        events_queue.erase(events_queue.begin(),events_queue.begin()+1);
        return event;
    }
    return NULL;
}

void ClientEventsManager::detectPlayerEvents(){

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

        orientation_t movementOrientation = FRONT;

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

        //MessageMovementPlayer* message = new MessageMovementPlayer(movementOrientation);  
        //client->sendMessage(message);
    }
}