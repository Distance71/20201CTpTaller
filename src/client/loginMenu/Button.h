#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../common/providers/GameProvider.h"
#include "../../common/models/Sprite.h"
#include "../../common/types.h"

using namespace std;

class Button{

    public:
        Button(int _xpos, int _ypos ,int _button_width,int _button_height,const char* not_selected_img_path,const char* selected_img_path);
        ~Button();
        bool isSelected();
        void update(int x, int y,bool click,bool force_selected_sprite);
        
    protected:
        SDL_Renderer* gRenderer;
        buttonstate_t state;
        Sprite* not_selected_sprite;
        Sprite* selected_sprite;
        int x_pos;
        int y_pos;        
        int button_width;
        int button_height;
        void selectState(int x, int y,bool click);       
};

#endif