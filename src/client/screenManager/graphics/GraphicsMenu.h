#ifndef _GRAPHICS_MENU_H_
#define _GRAPHICS_MENU_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "graphicElements/Button.h"
#include "graphicElements/TextBox.h"
#include "graphicElements/Image.h"
#include <string>
#include "../../../common/models/Sprite.h"
#include "../../../common/providers/GameProvider.h"
#include "../../Client.h"
#include  "../../../common/models/messages/MessageRequestLoginPlayer.h"
#include "../../../common/types.h"
#include "../../../common/services/Logger.h"
#include "../../audio/Audio.h"

class Client;

class GraphicsMenu {

    public:
        GraphicsMenu(Client* clientOwn);
        ~GraphicsMenu();
        void processEvent();
        void setLoginResponse(responseStatus_t response);
        void checkStatus();
        void show();
        
        
    private:
        SDL_Renderer* gRenderer;
        unordered_map <string, Image*> menuImages_; 
        unordered_map <string, Button*> buttons; 
        unordered_map <string, TextBox*> text_boxes;
        responseStatus_t response_;
        Client* clientOwn_;

        void addButton(string button_name,Button* button);
        void addTextBox(string text_box_name,TextBox* text_box);
        void addImage(string element_name,Image* image);
        void update(int x,int y, bool update);
        void sendCredentialsMessage();
        
};

#endif
