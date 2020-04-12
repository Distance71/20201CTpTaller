//Libraries inclusion
#include "../services/logger.h"
#include "../services/configurationHandler.h"
#include <SDL.h>

using namespace std;

struct status_t {
    bool normalStatus = true;
    string errorLog;
};

namespace GameProvider {

    Logger *logger_;

    Logger* getLogger() {
        return logger_;
    }

    void setLog(Logger *logger){
        logger_ = logger;
    }

    ConfigurationHandler *configuration_;

    ConfigurationHandler* getConfig() {
        return configuration_;
    }

    void setConfig(ConfigurationHandler *configuration){
        configuration_ = configuration;
    }

    status_t status_;

    status_t& getStatus(){
        return status_;
    }

    void setErrorStatus(string error){
        status_.normalStatus = false;
        status_.errorLog = error;
    }

    SDL_Renderer *renderer_;

    SDL_Renderer* getRenderer(){
        return renderer_;
    }

    void setRenderer(SDL_Renderer *renderer){
        renderer_ = renderer;
    }
}