#ifndef _GAMEPROVIDER_H_
#define _GAMEPROVIDER_H_

//Libraries inclusion

class ConfigurationHandler;

#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "../types.h"
#include "SDL2/SDL.h"
#include <string>
#include <unordered_map>

//Consts: should go in a config file
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define ELEMENT_SIZE 100

#define STAGE1LAYER1SPEED 0
#define STAGE1LAYER2SPEED 0
#define STAGE1LAYER3SPEED 3
#define STAGE1LAYER4SPEED 5
#define STAGE1LAYER5SPEED 7
#define STAGE1LAYER6SPEED 9
#define STAGE1LAYER7SPEED 10

#define MS_PER_UPDATE 14

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
    void setWindow(SDL_Window* window);
    SDL_Window* getWindow();

    //Could go later on gameParamsProvider
    void setWidth(size_t width);
    void setHeight(size_t height);
    int getElementsSize();
    void setQuantityPlayers(size_t quantityPlayers);
    size_t getWidth();
    size_t getHeight();
    gameZone_t getGameZone();
    size_t getQuantityPlayers();
    float getElaptedTimeFPS();
    unordered_map<layer_t, size_t> getLayersSpeeds(); //Possible refactor if add more levels
    loginScreen_t getLoginScreen();
    
    bool isValidCredential(string userName, string password);
    void setIdUser(string userName, Id idUser);
};

#endif