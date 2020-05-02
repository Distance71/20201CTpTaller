#include "PlayerController.h"
#include "MovementHandler.h"

//PlayerController::~PlayerController();

PlayerController::PlayerController(int id): MovementHandler(id){
}

int PlayerController::detect_event(){

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);  //Me da un arreglo con el estado de todas las teclas (1 presionada, 0 no presionada)
    
    Uint8 up =  keystate[SDL_SCANCODE_UP];
    Uint8 down = keystate[SDL_SCANCODE_DOWN];
    Uint8 right =  keystate[SDL_SCANCODE_RIGHT];
    Uint8 left = keystate[SDL_SCANCODE_LEFT];

    if (up && !down && !right && !left){ //arriba
       move_in_direction("up");
    }else if(!up && down && !right && !left){ // abajo
        move_in_direction("down");
    }else if(!up && !down && right && !left){ // derecha
        move_in_direction("left");
    }else if(!up && !down && !right && left){ // izquierda;
        move_in_direction("right");
    }else if(up && !down && right && !left){ // arriba a la derecha
        move_in_direction("top right");
    }else if(up && !down && !right && left){ // arriba a la izquierda
        move_in_direction("top left");
    }else if(!up && down && right && !left){ // abajo a la derecha
        move_in_direction("lower right");
    }else if(!up && down && !right && left){ // abajo a la izquierda
        move_in_direction("lower left");
    }
    
    return 0;
}