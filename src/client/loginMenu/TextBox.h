#ifndef _TEXTBOX_
#define _TEXTBOX_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Button.h"
#include <string>
#include "../../common/providers/GameProvider.h"

using namespace std;

class TextBox : public Button{
    
    public:
    TextBox(int _xpos, int _ypos ,const char* not_selected_img_path,const char* selected_img_path);
    void read_input(SDL_Event* e);
    void set_font(const char* font_path);
    void set_color(SDL_Color color);
    void update(int x, int y,bool click);
    void show_text(bool _showtext);
    void set_centering_parameters(int left,int right,int up,int down);
    
    private:
    bool showtext;
    string text;
    string substitution;
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Texture* create_text_texture();


    int x_centering_parameter_right;
    int x_centering_parameter_left;
    int y_centering_parameter_up;
    int y_centering_parameter_down;
};

#endif