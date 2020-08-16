#include "GameProvider.h"

namespace GameProvider {

    ConfigurationHandler *configuration_;
    status_t status_;
    SDL_Renderer *renderer_;
    SDL_Event lastEvent_;
    SDL_Window* _window;
    size_t screenWidth_;
    size_t screenHeight_;
    size_t quantityPlayers_;

    size_t getQuantityPlayers(){
        return quantityPlayers_;
    }

    void setQuantityPlayers(size_t quantityPlayers){
        quantityPlayers_ = quantityPlayers;
    }

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

    int getElementsSize(){
        return ELEMENT_SIZE;
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

    loginScreen_t getLoginScreen(){
        auto gameSettings = GameProvider::getConfig()->getGameParams();

        return gameSettings.loginScreen;
    }

    bool isValidCredential(string userName, string password){
        auto gameSettings = GameProvider::getConfig()->getGameParams();

        for (auto oneUser : gameSettings.playersParams){
            if (oneUser.username == userName)
                if (oneUser.password == password)
                    return true;
        }

        return false;
    }

    void setIdUser(string userName, Id idUser){
        auto gameSettings = GameProvider::getConfig()->getGameParams();

        for (auto oneUser : gameSettings.playersParams){
            if (oneUser.username == userName)
                oneUser.id = idUser;
        }
    }

    gameZone_t getGameZone(){

        gameZone_t zone;
        zone.xInit = 0;
        zone.xEnd = (int) screenWidth_;
        
        if (quantityPlayers_ <= 2) 
            zone.yInit = 110;
        else
            zone.yInit = 200;
        
        zone.yEnd = (int) screenHeight_;
        return zone;
    }
}

