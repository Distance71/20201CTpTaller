#include "MenuElement.h"

MenuElement::MenuElement(int _xpos,int _ypos,int _width,int _height,const char* image_path){
    gRenderer = GameProvider::getRenderer();
    sprite = new Sprite(image_path);
    xpos = _xpos;
    ypos = _ypos;
    width = _width;
    height = _height;
}



MenuElement::~MenuElement(){
    delete sprite;
}



void MenuElement::renderCopy(){
    if (width>0 && height>0){
        SDL_Rect rect = {xpos,ypos,width,height};
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,&rect);
    }
    else{
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,NULL);
    }
}