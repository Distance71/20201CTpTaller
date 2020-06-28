#include "PlayerController.h"

//PlayerController::~PlayerController();

PlayerController::PlayerController(Sprite* sprite_){
    sprite = sprite_;
}

void PlayerController::update(unordered_map<string, State *> states_){
    Logger::getInstance()->log(DEBUG, "Entro a player controller");

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);  //Me da un arreglo con el estado de todas las teclas (1 presionada, 0 no presionada)
    
    
    Uint8 up =  keystate[SDL_SCANCODE_UP];
    Uint8 down = keystate[SDL_SCANCODE_DOWN];
    Uint8 right =  keystate[SDL_SCANCODE_RIGHT];
    Uint8 left = keystate[SDL_SCANCODE_LEFT];

    int sprite_width = sprite->getTextureWidth();
    int sprite_height = sprite->getTextureHeight();

    int screen_widht = GameProvider::getWidth();
    int screen_height = GameProvider::getHeight();

    State* position = states_.at("Position");
    State* speed =states_.at("Speed");
    State* orientation = states_.at("Orientation");
    int xp = position->getX();
    int yp = position->getY();
    int xs = speed->getX();
    int ys = speed-> getY();

    int new_xp;
    int new_yp;
    
    if (up && !down && !right && !left){ //arriba
        new_yp=yp-ys;
        if (new_yp>=0){
            position->setY(new_yp);
        }
    }
    
    else if(!up && down && !right && !left){ // abajo
        new_yp=yp+ys;
        if(new_yp<=(screen_height-sprite_height)){
            position->setY(new_yp);
        }
    }
    
    else if(!up && !down && right && !left){ // derecha
        new_xp=xp+xs;
        orientation->setX(FRONT);
        if(new_xp<=screen_widht-sprite_width){
            position->setX(new_xp);
        }
    }
    
    else if(!up && !down && !right && left){ // izquierda;
        new_xp=xp-xs;
        orientation->setX(BACK);
        if(new_xp>=0){
            position->setX(new_xp);
        }
    }

    else if(up && !down && right && !left){ // arriba a la derecha
        new_xp=xp+xs;
        new_yp=yp-ys;
        orientation->setX(FRONT);

        if (new_xp <=screen_widht-sprite_width){
            position->setX(new_xp);
        }

        if (new_yp>0){
            position->setY(new_yp);

        }
    }
    
    
    else if(up && !down && !right && left){ // arriba a la izquierda
        new_xp=xp-xs;
        new_yp=yp-ys;
        orientation->setX(BACK);

        if (new_xp >=0 ){
            position->setX(new_xp);
        }

        if (new_yp>=0){
            position->setY(new_yp);

        }
    }
    
    
    
    else if(!up && down && right && !left){ // abajo a la derecha
        new_xp=xp+xs;
        new_yp=yp+ys;
        orientation->setX(FRONT);

        if (new_xp <= screen_widht-sprite_width){
            position->setX(new_xp);
        }

        if (new_yp<=screen_height-sprite_height){
            position->setY(new_yp);

        }
    }
    
    else if(!up && down && !right && left){ // abajo a la izquierda
        new_xp=xp-xs;
        new_yp=yp+ys;
        orientation->setX(BACK);
        if (new_xp >= 0){
            position->setX(new_xp);
        }

        if (new_yp<=(screen_height-sprite_height)){
            position->setY(new_yp);

        }
    }
}