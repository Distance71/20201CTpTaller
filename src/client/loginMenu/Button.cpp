#include "Button.h"
#include <stdio.h>

Button::Button(int _xpos, int _ypos ,const char* not_selected_img_path,const char* selected_img_path){
    gRenderer=GameProvider::getRenderer();
    not_selected_sprite= new Sprite(not_selected_img_path);
    selected_sprite= new Sprite(selected_img_path);
    x_pos=_xpos;
    y_pos=_ypos;
    state = NOT_SELECTED;
}


void Button::select_state(int x, int y,bool click){

    Sprite* actual_sprite =NULL;

    if (state==NOT_SELECTED){
        actual_sprite=not_selected_sprite;
    }
    else{
        actual_sprite=selected_sprite;
    }

    int x_limit_1 = x_pos;
    int x_limit_2 = x_pos + actual_sprite-> getTextureWidth();
    int y_limit_1 = y_pos;
    int y_limit_2 = y_pos + actual_sprite->getTextureHeight();


    if(x>= x_limit_1 && x<=x_limit_2 && y>= y_limit_1 && y<=y_limit_2){
        if (click){
            state = SELECTED;
        }
    } 
    else{
        if (click){
            state=NOT_SELECTED;
        }
    }
}

void Button::execute_action(){}

void Button::update(int x, int y,bool click,bool force_selected_sprite){
    
    select_state(x,y,click);
    
    Sprite* actual_sprite =NULL;

    if (state==NOT_SELECTED && !force_selected_sprite){
        actual_sprite=not_selected_sprite;
    }
    else{
        actual_sprite=selected_sprite;
    }
    
    int width=actual_sprite->getTextureWidth();
    int height=actual_sprite->getTextureHeight();
   
    SDL_Rect button ={this->x_pos,this->y_pos, width, height}; 
    SDL_Rect rect = {0,0, width, height};
    
    SDL_RenderCopy( gRenderer, actual_sprite->getTexture(),&rect,&button);

}