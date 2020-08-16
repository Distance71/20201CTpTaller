#ifndef _IMAGE_
#define _IMAGE_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../../../common/models/Sprite.h"
#include "../../../../common/providers/GameProvider.h"

using namespace std;

class Image {
    
    public:  
    Image(const char* image_path);
    ~Image();
    void renderCopy(int xpos,int ypos,int width,int height);

    private:
    SDL_Renderer* gRenderer; 
    Sprite* sprite;
};

#endif