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
#include "SDL2/SDL_mixer.h"
#include "graphics/GraphicsMenu.h"
#include "graphics/GameGraphics.h"
#include "../common/types.h"
#include "../common/models/Sprite.h"

class Client;
class GraphicsMenu;

class ScreenManager{
   
    private:
        Client *clientOwn_;
        bool quit_;
        int screenWidth_;
        int screenHeight_;
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        GraphicsMenu* menu_;
        GameGraphics* gameGraphics_;
        Sprite* loading_;

        bool initGraphicsMenu();
        bool initSDL();
        bool initGameGraphics();


    public:
        ScreenManager(Client *client);
        ~ScreenManager();
        void setScreenSizes(int Xsize, int YSize);
        bool initializeGraphics();
        void viewLogin();
        void updateEntity(elementType_t type, position_t position);
        void updateBackgroundLayer(layer_t layer, stage_t stage, int step);
        void setImage(sceneScreen_t scene);
        void setLoginResponse(responseStatus_t response);
        void stopWaiting();
        void viewEndGameScreen();
        Client* getClient();
        SDL_Renderer* getRenderer();
        void ServerDisconnection();
        GraphicsMenu* getGraphicsMenu();
};

#endif
