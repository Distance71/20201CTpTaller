#include "GameProvider.h"

namespace GameProvider {

    Logger *logger_;
    ConfigurationHandler *configuration_;
    status_t status_;
    SDL_Renderer *renderer_;
    SDL_Event lastEvent_;

    size_t getWidth() {
        return SCREEN_WIDTH;
    }

    size_t getHeight(){
        return SCREEN_HEIGHT;
    }

    SDL_Event getLastEvent() {
        return lastEvent_;
    }

    void setLastEvent(SDL_Event lastEvent) {
        lastEvent_ = lastEvent;
    }

    Logger* getLogger() {
        return logger_;
    }

    void setLog(Logger *logger){
        logger_ = logger;
    }

    ConfigurationHandler* getConfig() {
        return configuration_;
    }

    void setConfig(ConfigurationHandler *configuration){
        configuration_ = configuration;
    }

    status_t& getStatus(){
        return status_;
    }

    void setNormalExitStatus() {
        status_.normalStatus = false;
    }

    void setErrorStatus(string error){
        status_.normalStatus = false;
        status_.errorLog = error;
    }

    //Should go in a config file or related to configurationHandler
    float getElaptedTimeFPS() {
        return MS_PER_UPDATE;
    }

    SDL_Renderer* getRenderer(){
        return renderer_;
    }

    void setRenderer(SDL_Renderer *renderer){
        renderer_ = renderer;
    }
}