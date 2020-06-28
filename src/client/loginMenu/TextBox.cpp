#include "TextBox.h"
#include <stdio.h>

TextBox::TextBox(int _xpos, int _ypos ,const char* not_selected_img_path,const char* selected_img_path):Button(_xpos,_ypos,not_selected_img_path, selected_img_path){
    text="";
    set_font("font/font2.ttf");
    SDL_Color default_color ={135,206,255};
    set_color(default_color);
    showtext=true;

    x_centering_parameter_right=10;
    x_centering_parameter_left=40;
    y_centering_parameter_up=15;
    y_centering_parameter_down=10;
}




void TextBox::set_font(const char* font_path){
    font = TTF_OpenFont( "font/font.ttf",24);
    if( font == NULL ){
        printf( "unable to load font");
    }
}




void TextBox::set_color(SDL_Color color){
    textColor = color;
}




void TextBox::read_input(SDL_Event* e){
    if (state==SELECTED){
        if( e->type == SDL_KEYDOWN){
            if( e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 ){
                //lop off character
                text.pop_back();
                substitution.pop_back();
            }     
        }
        else if(e->type==SDL_TEXTINPUT){
            text += e->text.text;
            substitution+="*";
        }
    }
}

void TextBox::set_centering_parameters(int left,int right,int up,int down){
    x_centering_parameter_left=left;
    x_centering_parameter_right=right;
    y_centering_parameter_up=up;
    y_centering_parameter_down=down;
}


SDL_Texture* TextBox:: create_text_texture(){

    const char* _text;

    if (text==""){
        _text=" ";
    }
    else if (showtext){
        _text=text.c_str();
    }
    else{
        _text=substitution.c_str();  
    }
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,_text, textColor);
    
    if( textSurface == NULL ){
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        return NULL;
    }

    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if( text_texture  == NULL){
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return NULL;
    }
    
    SDL_FreeSurface(textSurface);
    
    return text_texture;
}
 
void TextBox::show_text(bool _showtext){
    showtext=_showtext;
}

void TextBox::update(int x, int y,bool click){
    
    bool force_selected_sprite = false;
    if (text.length()!=0){
        force_selected_sprite=true;
    }
    
    Button::update(x,y,click,force_selected_sprite);

    /*Text texture creation*/
        SDL_Texture* text_texture = create_text_texture();
        int text_texture_width;
        int text_texture_height;
        SDL_QueryTexture(text_texture, nullptr, nullptr, &text_texture_width,NULL);
        SDL_QueryTexture(text_texture, nullptr, nullptr,NULL,&text_texture_height);
        
        /*Rendering text texture*/


        int y_begin_position = y_pos + y_centering_parameter_up;
        int y_end_position = y_pos + selected_sprite->getTextureHeight() - y_centering_parameter_down;
        int x_begin_position = x_pos + x_centering_parameter_left;
        int x_end_position;

        /* el ancho del container depende del texto por lo que varia acorde a eso su posicion final*/
        
        /*CASO1: texto más corto que el espacio del que dispongo*/
        if (text_texture_width<(selected_sprite->getTextureWidth()-x_centering_parameter_right-x_centering_parameter_left)){
            x_end_position = x_begin_position + text_texture_width;
        }
        else{
        /*CASO2: texto más largo que el ancho del sprite*/
        x_end_position = x_begin_position + selected_sprite->getTextureWidth()- x_centering_parameter_left - x_centering_parameter_right;
        }
        
        /*Calculo ancho y alto del contenedor*/
        int text_container_width = x_end_position - x_begin_position;
        int text_container_height = y_end_position - y_begin_position;

        /*Creo el contenedor*/
        SDL_Rect text_container = {x_begin_position,y_begin_position, text_container_width, text_container_height};


        /*Selecciono el texto a mostrar*/ 
        int x_begin;

        if (text_texture_width <= text_container_width){
            x_begin= 0;
        }
        else{
            x_begin = text_texture_width - text_container_width;
        }
    
        SDL_Rect text_selection = {x_begin,0,text_texture_width,text_texture_height};
        
        /*Rendering text*/
        SDL_RenderCopy(gRenderer, text_texture,&text_selection,&text_container);
}
