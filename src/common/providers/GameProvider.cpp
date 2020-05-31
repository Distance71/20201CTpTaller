#include "GameProvider.h"

namespace GameProvider {

    ConfigurationHandler *configuration_;
    status_t status_;
    SDL_Renderer *renderer_;
    SDL_Event lastEvent_;
    SDL_Window* _window;
    size_t screenWidth_;
    size_t screenHeight_;

    size_t getWidth() {
        return screenWidth_;
    }

    size_t getHeight(){
        return screenHeight_;
    }

    void setWidth(size_t width) {
        screenWidth_ = width;
    }

    void setHeight(size_t height){
        screenHeight_ = height;
    }

    SDL_Event getLastEvent() {
        return lastEvent_;
    }

    void setLastEvent(SDL_Event lastEvent) {
        lastEvent_ = lastEvent;
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

    SDL_Window* getWindow(){
        return _window;
    }

    void setWindow(SDL_Window* window){
        _window= window;
    }

    void setRenderer(SDL_Renderer *renderer){
        renderer_ = renderer;
    }

    unordered_map<layer_t, size_t> getLayersSpeeds(){
        unordered_map<layer_t, size_t> layersSpeeds = {
            {LAYER_1, STAGE1LAYER1SPEED}, 
            {LAYER_2, STAGE1LAYER2SPEED}, 
            {LAYER_3, STAGE1LAYER3SPEED},
            {LAYER_4, STAGE1LAYER4SPEED},
            {LAYER_5, STAGE1LAYER5SPEED},
            {LAYER_6, STAGE1LAYER6SPEED},
            {LAYER_7, STAGE1LAYER7SPEED},
            };

        return layersSpeeds;
    }
}