#include "Image.h"

Image::Image(int _width,int _height,const char* image_path){
    gRenderer = GameProvider::getRenderer();
    sprite = new Sprite(image_path);
    width = _width;
    height = _height;
}



Image::~Image(){
    delete sprite;
}


void Image::renderCopy(int xpos,int ypos){
    if (width>0 && height>0){
        SDL_Rect rect = {xpos,ypos,width,height};
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,&rect);
    }
    else{
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,NULL);
    }
}