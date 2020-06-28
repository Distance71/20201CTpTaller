#ifndef _MENU_H_
#define _MENU_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "Button.h"
#include "TextBox.h"
#include <string>
#include "../../common/models/Sprite.h"
#include "../../common/providers/GameProvider.h"


using namespace std;

class  Menu {

    public:
        Menu();
        void run();
         
    private:
        Sprite* background;

    unordered_map <string, Button *> buttons; //BOTONES QUE EJECUTAN ACCIONES
    unordered_map <string, TextBox *> text_boxes; // CUADROS DE TEXTO

        SDL_Renderer* gRenderer; 
        void add_button(string button_name,Button* button);
        void add_textBox(string text_button_name,TextBox* text_button);
        void show();
        void update(int x,int y, bool update);  
};

#endif
