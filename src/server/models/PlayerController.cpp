#include "PlayerController.h"

PlayerController::PlayerController(Sprite* sprite_){
    sprite = sprite_;
}

void PlayerController::update(unordered_map<string, State *> states_){
    cout <<"entro"<<endl;
    Logger::getInstance()->log(DEBUG, "Entro a player controller");

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);  //Me da un arreglo con el estado de todas las teclas (1 presionada, 0 no presionada)
    
    
    Uint8 up =  keystate[SDL_SCANCODE_UP];
    Uint8 down = keystate[SDL_SCANCODE_DOWN];
    Uint8 right =  keystate[SDL_SCANCODE_RIGHT];
    Uint8 left = keystate[SDL_SCANCODE_LEFT];

    int sprite_width = sprite->getTextureWidth();
    int sprite_height = sprite->getTextureHeight();

    gameZone_t zone = GameProvider::getGameZone();

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
        cout <<zone.xInit<<endl;
        if (new_yp>=zone.yInit){
            cout <<zone.xInit<<endl;
            position->setY(new_yp);
        }
    }
    
    else if(!up && down && !right && !left){ // abajo
        new_yp=yp+ys;
        if(new_yp<=(zone.yEnd-sprite_height)){
            position->setY(new_yp);
        }
    }
    
    else if(!up && !down && right && !left){ // derecha
        new_xp=xp+xs;
        orientation->setX(FRONT);
        if(new_xp<=zone.xEnd-sprite_width){
            position->setX(new_xp);
        }
    }
    
    else if(!up && !down && !right && left){ // izquierda;
        new_xp=xp-xs;
        orientation->setX(BACK);
        if(new_xp>=zone.xInit){
            position->setX(new_xp);
        }
    }

    else if(up && !down && right && !left){ // arriba a la derecha
        new_xp=xp+xs;
        new_yp=yp-ys;
        orientation->setX(FRONT);

        if (new_xp <=zone.xEnd-sprite_width){
            position->setX(new_xp);
        }

        if (new_yp>zone.yInit){
            position->setY(new_yp);

        }
    }
    
    
    else if(up && !down && !right && left){ // arriba a la izquierda
        new_xp=xp-xs;
        new_yp=yp-ys;
        orientation->setX(BACK);

        if (new_xp >=zone.xInit){
            position->setX(new_xp);
        }

        if (new_yp>=zone.yInit){
            position->setY(new_yp);

        }
    }
    
    
    
    else if(!up && down && right && !left){ // abajo a la derecha
        new_xp=xp+xs;
        new_yp=yp+ys;
        orientation->setX(FRONT);

        if (new_xp <= zone.xEnd-sprite_width){
            position->setX(new_xp);
        }

        if (new_yp<=zone.yEnd-sprite_height){
            position->setY(new_yp);

        }
    }
    
    else if(!up && down && !right && left){ // abajo a la izquierda
        new_xp=xp-xs;
        new_yp=yp+ys;
        orientation->setX(BACK);
        if (new_xp >= zone.xInit){
            position->setX(new_xp);
        }

        if (new_yp<=(zone.yEnd-sprite_height)){
            position->setY(new_yp);

        }
    }
}