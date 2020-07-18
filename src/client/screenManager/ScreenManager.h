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
        bool waiting_;


        bool initMenu();
        bool initSDL();
        bool initGameGraphics();


    public:
        ScreenManager(Client *client);
        ~ScreenManager();
        void setScreenSizes(int Xsize, int YSize);
        bool initializeGraphics();
        bool viewLogin();
        void graphic();
        void updateEntity(elementType_t type, position_t position);
        void setBackground(level_t level);
        void setImage(sceneScreen_t scene);
        void setLoginResponse(responseStatus_t response);
        int waitForPlayers();
        void stopWaiting();
        void viewEndGameScreen();
        Client* getClient();
        SDL_Renderer* getRenderer();
        void runScreenGraphicsThread();
};

#endif
