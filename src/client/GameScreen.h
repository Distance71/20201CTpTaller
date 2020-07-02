#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include <iostream>
#include <strings.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Client.h"
#include "clientModels/ClientMap.h"
#include "../common/providers/GameProvider.h"
#include "../common/types.h"

using namespace std;

class ClientMap;
class Client;
class ClientMap;

class GameScreen {
    private:
        Client *clientOwn;
        ClientMap *map_;
        SDL_Window *window_ = nullptr;
        SDL_Renderer *renderer_ = nullptr;

        bool waitEnter(SDL_Surface* screen);

    public:
        GameScreen(Client *client);
        ~GameScreen();

        void initializeGraphics();
        void clearScene();
        void processEvent();
        void updateGraphics();

        void addLayer(size_t idLayer, string sourceLayer);

        int viewLogin();
        bool viewStartStage(level_t oneLevel);
        bool viewStageCleared(level_t oneLevel);
};

#endif
