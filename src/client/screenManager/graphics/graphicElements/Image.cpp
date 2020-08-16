#include "Image.h"

Image::Image(const char* image_path){
    gRenderer = GameProvider::getRenderer();
    sprite = new Sprite(image_path);
}



Image::~Image(){
    delete sprite;
}


void Image::renderCopy(int xpos,int ypos,int width,int height){
    if (width>0 && height>0){
        SDL_Rect rect = {xpos,ypos,width,height};
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,&rect);
    }
    else{
        SDL_RenderCopy(gRenderer,sprite->getTexture(),NULL,NULL);
    }
}