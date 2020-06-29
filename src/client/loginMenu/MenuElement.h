#ifndef _MENU_ELEMENT_
#define _MENU_ELEMENT_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../common/models/Sprite.h"
#include "../../common/providers/GameProvider.h"

using namespace std;

class MenuElement {
    
    public:
    MenuElement(int _xpos,int _ypos,int _width,int _height,const char* image_path);
    ~MenuElement();
    void renderCopy();

    private:
    SDL_Renderer* gRenderer;
    Sprite* sprite;
    int xpos;
    int ypos;
    int width;
    int height;
};

#endif