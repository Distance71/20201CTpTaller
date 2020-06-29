#ifndef _TEXTBOX_
#define _TEXTBOX_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "Button.h"
#include <string>
#include "../../common/providers/GameProvider.h"
#include "../common/services/Logger.h"

using namespace std;

class TextBox : public Button{
    
    public:
        TextBox(int _xpos, int _ypos ,int _button_width,int _button_height,const char* not_selected_img_path,const char* selected_img_path);
        ~TextBox();
        void readInput(SDL_Event* e);
        void setFont(const char* font_path,int size);
        void setColor(SDL_Color color);
        void hideText(bool _hidetext);
        void setCenteringParameters(int left,int right,int up,int down);
        void update(int x, int y,bool click);
        const char* getText();
        

    private:
        string text;
        string substitution;
        TTF_Font* font;
        SDL_Color textColor;
        bool hidetext;
        int x_centering_parameter_left;
        int x_centering_parameter_right;
        int y_centering_parameter_up;
        int y_centering_parameter_down;
        SDL_Texture* createTextTexture();
 
};

#endif