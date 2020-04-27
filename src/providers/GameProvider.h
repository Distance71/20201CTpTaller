#ifndef _GAMEPROVIDER_H_
#define _GAMEPROVIDER_H_

//Libraries inclusion

#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "SDL2/SDL.h"

//Consts: should go in a config file
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MS_PER_UPDATE 16.67

struct status_t {
    bool normalStatus = true;
    string errorLog;
};

// Contiene todas las variables que pueden ser comunes a todo el programa
// y su manejo.

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
    
    //Could go later on configurationHandler
    size_t getWidth();
    size_t getHeight();
    float getElaptedTimeFPS();
};

#endif