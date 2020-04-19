#ifndef _GAMEPROVIDER_H_
#define _GAMEPROVIDER_H_

//Libraries inclusion

#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "SDL2/SDL.h"

struct status_t {
    bool normalStatus = true;
    string errorLog;
};

// Contiene todas las variables que pueden ser comunes a todo el programa
// y su manejo.

namespace GameProvider {
    SDL_Event getLastEvent();
    void setLastEvent(SDL_Event lastEvent);
    Logger* getLogger();
    void setLog(Logger *logger);
    ConfigurationHandler* getConfig();
    void setConfig(ConfigurationHandler *configuration);
    status_t& getStatus();
    void setNormalExitStatus();
    void setErrorStatus(string error);
    SDL_Renderer* getRenderer();
    void setRenderer(SDL_Renderer *renderer);
};

#endif