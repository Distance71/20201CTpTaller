#ifndef _GAMEPROVIDER_H_
#define _GAMEPROVIDER_H_

//Libraries inclusion

#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "SDL2/SDL.h"
#include <unordered_map>

//Consts: should go in a config file
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define STAGE1LAYER1SPEED 0
#define STAGE1LAYER2SPEED 2
#define STAGE1LAYER3SPEED 5 

#define MS_PER_UPDATE 16.67

struct status_t {
    bool normalStatus = true;
    string errorLog;
};

// Contiene todas las variables que pueden ser comunes a todo el programa
// y su manejo.

enum layer_t {LAYER_1 = 0, LAYER_2 = 1, LAYER_3 = 2};

namespace GameProvider {
    SDL_Event getLastEvent();
    void setLastEvent(SDL_Event lastEvent);
    ConfigurationHandler* getConfig();
    void setConfig(ConfigurationHandler *configuration);
    status_t& getStatus();
    void setNormalExitStatus();
    void setErrorStatus(string error);
    SDL_Renderer* getRenderer();
    void setRenderer(SDL_Renderer *renderer);
    void setWindow(SDL_Window* window);
    SDL_Window* getWindow();

    //Could go later on gameParamsProvider
    size_t getWidth();
    size_t getHeight();
    float getElaptedTimeFPS();
    unordered_map<layer_t, size_t> getLayersSpeeds(); //Possible refactor if add more levels

};

#endif