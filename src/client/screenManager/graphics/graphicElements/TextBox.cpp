#include "TextBox.h"
#include <stdio.h>

TextBox::TextBox(int _xpos, int _ypos ,int _button_width,int _button_height,const char* not_selected_img_path,const char* selected_img_path):Button(_xpos,_ypos,_button_width,_button_height,not_selected_img_path, selected_img_path){
    text="";
    substitution="";
    setFont("assets/Fonts/open-sans/OpenSans-Bold.ttf",24);
    setColor({135,206,255});
    hidetext = false;
    x_centering_parameter_left = 0;
    x_centering_parameter_right = 0;
    y_centering_parameter_up = 0;
    y_centering_parameter_down = 0;
}


TextBox::~TextBox(){
    TTF_CloseFont(font);
}


void TextBox::setFont(const char* font_path,int size){
    TTF_Font* _font = TTF_OpenFont(font_path,size);
    if(!_font){
         Logger::getInstance()->log(ERROR,string("No se pudo cargar la fuente: ") + TTF_GetError());
    }
    else{
        font = _font;
    }
}



void TextBox::setColor(SDL_Color color){
    textColor = color;
}



void TextBox::readInput(SDL_Event* e){
    if (state == SELECTED){
        if( e->type == SDL_KEYDOWN){
            if( e->key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 ){
                text.pop_back();
                substitution.pop_back();
            }     
        }
        else if(e->type == SDL_TEXTINPUT){
            text += e->text.text;
            substitution += "*";
        }
    }
}

void TextBox::setText(string newtext){
    this->text = newtext;
    substitution= "";
    for (int i=0; i<newtext.length();i++){
        substitution += "*";
    }
}



void TextBox::hideText(bool _hidetext){
    hidetext=_hidetext;
}



void TextBox::setCenteringParameters(int left,int right,int up,int down){
    x_centering_parameter_left = left;
    x_centering_parameter_right = right;
    y_centering_parameter_up = up;
    y_centering_parameter_down = down;
}



SDL_Texture* TextBox:: createTextTexture(){
    const char* _text;
    
    if (!hidetext){
        if (text=="")
            _text=" ";
        else
            _text = text.c_str();  
    }
    
    else{
        if (substitution=="")
            _text=" ";
        else
           _text = substitution.c_str(); 
    }

    SDL_Surface* text_surface = TTF_RenderText_Solid(font,_text, textColor);
    if(!text_surface){
        Logger::getInstance()->log(ERROR,string("No se pudo crear la superficie, SDL_ttf Error: ") + TTF_GetError());
        return NULL;
    }
    else{
        SDL_Texture* text_texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
        if(!text_texture){
            Logger::getInstance()->log(ERROR,string("No se pudo crear la textura para el texto, SDL_ttf Error: ") + TTF_GetError());
            SDL_FreeSurface(text_surface);
            return NULL;
        }
        SDL_FreeSurface(text_surface);
        return text_texture;
    }
}


const char* TextBox::getText(){
    return text.c_str();
}



void TextBox::update(int x, int y,bool click){
    /*Updating sprites*/
    bool force_selected_sprite = false;
    if (text.length()>0){
        force_selected_sprite=true;
    }
    Button::update(x,y,click,force_selected_sprite);

    /*Text texture creation*/
    SDL_Texture* text_texture = createTextTexture();
    int text_texture_width;
    int text_texture_height;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &text_texture_width,NULL);
    SDL_QueryTexture(text_texture, nullptr, nullptr,NULL,&text_texture_height);
        
    /*setting drawing box limits*/
    int y_begin_position = y_pos + y_centering_parameter_up;
    int y_end_position = y_pos + button_height - y_centering_parameter_down;
    int x_begin_position = x_pos + x_centering_parameter_left;
    int x_end_position;
    if (text_texture_width<(button_width-x_centering_parameter_right-x_centering_parameter_left)){
        x_end_position = x_begin_position + text_texture_width;
    }
    else{
        x_end_position = x_begin_position + button_width - x_centering_parameter_left - x_centering_parameter_right;
    }
        
    int drawing_box_width = x_end_position - x_begin_position;
    int drawing_box_height = y_end_position - y_begin_position;

    /*drawing box creation*/
    SDL_Rect text_container = {x_begin_position,y_begin_position, drawing_box_width, drawing_box_height};

    /*Selecting the text to show*/ 
    int x_begin;
    if (text_texture_width <= drawing_box_width){
            x_begin= 0;
    }
    else{
        x_begin = text_texture_width - drawing_box_width;
    }
    
    SDL_Rect text_selection = {x_begin,0,text_texture_width,text_texture_height};
        
    /*Rendering text*/
    SDL_RenderCopy(gRenderer, text_texture,&text_selection,&text_container);

    SDL_DestroyTexture(text_texture);
}
