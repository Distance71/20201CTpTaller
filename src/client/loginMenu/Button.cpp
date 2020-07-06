#include "Button.h"

Button::Button(int _xpos, int _ypos ,int _button_width, int _button_height,const char* not_selected_img_path,const char* selected_img_path){
    gRenderer=GameProvider::getRenderer();
    not_selected_sprite=new Sprite(not_selected_img_path);
    selected_sprite=new Sprite(selected_img_path);
    button_width = _button_width;
    button_height = _button_height;
    x_pos=_xpos;
    y_pos=_ypos;
    state=NOT_SELECTED;
}



Button::~Button(){
    delete not_selected_sprite;
    delete selected_sprite;
}



void Button::selectState(int x, int y,bool click){
    Sprite* actual_sprite = NULL;
    if (state == NOT_SELECTED){
        actual_sprite = not_selected_sprite;
    }
    else{
        actual_sprite = selected_sprite;
    } 
    int x_limit_left = x_pos;
    int x_limit_right = x_pos+button_width;
    int y_limit_up = y_pos;
    int y_limit_down = y_pos+button_height; 
    if(x >= x_limit_left && x <= x_limit_right && y >= y_limit_up && y <= y_limit_down){
        if (click){
            state = SELECTED;
        }
    } 
    else{
        if (click){
            state = NOT_SELECTED;
        }
    }
}



bool Button::isSelected(){
    if (state==SELECTED){
        return true;
    }
    return false;
}




void Button::update(int x, int y,bool click,bool force_selected_sprite){
    selectState(x,y,click);  
    Sprite* actual_sprite = NULL;
    if (state == NOT_SELECTED && !force_selected_sprite){
        actual_sprite = not_selected_sprite;
    }
    else{
        actual_sprite = selected_sprite;
    }

    SDL_Rect button ={this->x_pos,this->y_pos, button_width, button_height}; 
 
    SDL_RenderCopy( gRenderer, actual_sprite->getTexture(),NULL,&button);
}

void Button::deselect(){
    state =  NOT_SELECTED;

}