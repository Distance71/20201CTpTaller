#ifndef _GAME_SCREEN_H_
#define _GAME_SCREEN_H_

#include <iostream>
#include <strings.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Client.h"
#include "../common/providers/GameProvider.h"
#include "../common/types.h"

using namespace std;

class Client;

class GameScreen {
    private:
        Client *clientOwn;
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

        void viewLogin();
        bool viewStartStage(level_t oneLevel);
        bool viewStageCleared(level_t oneLevel);
};

#endif