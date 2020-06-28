#include "Menu.h"
#include <stdio.h>

Menu::Menu(){

    printf("entre");
     //Initialize SDL_ttf
	if( TTF_Init() == -1 ){
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_StartTextInput();
    gRenderer = GameProvider::getRenderer();
    string aux("images/background.png");
    background=new Sprite(aux);
    /*TextBox* username = new TextBox(50,100,"images/username1.png","images/username2.png");
    add_textBox("USER",username);
    TextBox* password = new TextBox(50,200,"images/password1.png","images/password2.png");
    password->show_text(false);
    add_textBox("PASSWORD",password);
    Button* login = new Button(200,300,"images/login.png","images/login.png");
    add_button("LOGIN",login);*/
}


void Menu::add_button(string button_name,Button* button){
    buttons[button_name]= button;
}



void Menu::add_textBox(string text_button_name,TextBox* text_box){
    text_boxes[text_button_name]= text_box;
}



void Menu::update(int x, int y,bool click){
    SDL_RenderCopy(gRenderer,background->getTexture(),NULL,NULL);

    for(auto button : buttons){
        button.second->update(x,y,click,false);
    }
    for(auto text_box: text_boxes){
        text_box.second->update(x,y,click);    
    }
    
    
}

void Menu::run(){

    bool click = false;
    bool quit = false;
    SDL_Event e;
    int x = -1;
    int y = -1;
    while( !quit ){
        while(SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            
            else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN){
                SDL_GetMouseState(&x, &y);
                if (e.type==SDL_MOUSEBUTTONDOWN){
                    click= true;
                }
            }

            else if (e.type==SDL_KEYDOWN || e.type==SDL_TEXTINPUT){
                for(auto text_box : text_boxes){
                    text_box.second->read_input(&e);
                }    
            }
        } 

        update(x,y,click);    
        show();
        click=false;
    }
}



void Menu::show(){
    SDL_RenderPresent(gRenderer);
}

