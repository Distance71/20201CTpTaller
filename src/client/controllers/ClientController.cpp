#include "ClientController.h"

ClientController::ClientController(Client *client){
    this->clientOwn_ = client;
}

ClientController::~ClientController(){}

void ClientController::update(){

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);  //Me da un arreglo con el estado de todas las teclas (1 presionada, 0 no presionada)
    
    Uint8 up =  keystate[SDL_SCANCODE_UP];
    Uint8 down = keystate[SDL_SCANCODE_DOWN];
    Uint8 right =  keystate[SDL_SCANCODE_RIGHT];
    Uint8 left = keystate[SDL_SCANCODE_LEFT];

    orientation_t movementOrientation = FRONT;

    if (up && !down && !right && !left){ //arriba
        movementOrientation = UP;
    }
    
    else if(!up && down && !right && !left){ // abajo
        movementOrientation = DOWN;
    }
    
    else if(!up && !down && right && !left){ // derecha
        movementOrientation = FRONT;
    }
    
    else if(!up && !down && !right && left){ // izquierda;
        movementOrientation = BACK;
    }

    else if(up && !down && right && !left){ // arriba a la derecha
        movementOrientation = FRONT_UP;
    }
    
    else if(up && !down && !right && left){ // arriba a la izquierda
        movementOrientation = BACK_UP;
    }
    
    else if(!up && down && right && !left){ // abajo a la derecha
        movementOrientation = FRONT_DOWN;
    }
    
    else if(!up && down && !right && left){ // abajo a la izquierda
        movementOrientation = BACK_DOWN;
    }    

    // TODO: llamar metodo para enviar mensaje el Server
    this->clientOwn_->sendMovement(movementOrientation);
}