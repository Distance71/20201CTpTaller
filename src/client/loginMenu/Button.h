#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../common/providers/GameProvider.h"
#include "../../common/models/Sprite.h"

using namespace std;

typedef enum {
    SELECTED,
    NOT_SELECTED,
}menustate_t;


class Button{
    
    public:
        Button(int _xpos, int _ypos ,const char* not_selected_img_path,const char* selected_img_path);
        void select_state(int x, int y,bool click);
        void update(int x, int y,bool click,bool force_selected_sprite);
        void execute_action();
        

       
    private:
      
    
    protected:
        SDL_Renderer* gRenderer;
        menustate_t state;
        Sprite* not_selected_sprite;
        Sprite* selected_sprite;
        int x_pos;
        int y_pos;
              
};


#endif