#ifndef _SCREEN_MANAGER_H_
#define _SCREEN_MANAGER_H_

#include <iostream>
#include <strings.h>
#include <stdbool.h>
#include "../common/providers/GameProvider.h"
#include "../../common/services/Logger.h"
#include "Client.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "loginMenu/Menu.h"
#include "graphics/GameGraphics.h"
#include "../common/types.h"

class Client;
class Menu;

class ScreenManager{
   
    private:
        Client *clientOwn_;
        bool quit_;
        int screenWidth_;
        int screenHeight_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        Menu* menu_;
        GameGraphics* gameGraphics_;

        bool initMenu();
        bool initSDL();
        bool initGameGraphics();


    public:
        ScreenManager(Client *client);
        ~ScreenManager();
        void setScreenSizes(int Xsize, int YSize);
        bool initializeGraphics();
        bool viewLogin();
        void initGameGraphicsThread();
        void createEntity(IdElement id, const string &source, int sizeX, int sizeY, int posX, int posY, orientation_t orientation);
        void updateEntity(IdElement id, int posX, int posY, orientation_t orientation);
        void deadEntity(IdElement id);
        void setBackground(stageSource_t background);
        void setImage(const string &source);
        void setLoginResponse(responseStatus_t response);
};

#endif
