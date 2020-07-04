#ifndef _MENU_H_
#define _MENU_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "Button.h"
#include "TextBox.h"
#include "MenuElement.h"
#include <string>
#include "../../common/models/Sprite.h"
#include "../../common/providers/GameProvider.h"
#include "../Client.h"
#include  "../../common/models/messages/MessageRequestLoginPlayer.h"
#include "../../common/types.h"

using namespace std;
class Client;

class Menu {

    public:
        Menu(Client* _client);
        ~Menu();
        void processEvent();
        void show();
        void setCredentialsResponse(loginAnswer_t _answer);
        bool validateCredentials();
        
    private:
        Client* client;
        SDL_Renderer* gRenderer;
        unordered_map <string, MenuElement*> menu_elements; 
        unordered_map <string, Button*> buttons; 
        unordered_map <string, TextBox*> text_boxes;
        loginAnswer_t credentials_response;
        bool invalid_credentials;

        void addButton(string button_name,Button* button);
        void addTextBox(string text_box_name,TextBox* text_box);
        void addMenuElement(string element_name,MenuElement* menu_element);
        void update(int x,int y, bool update); 
        
};

#endif
