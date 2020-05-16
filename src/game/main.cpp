#include "models/Game.h"
#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "../providers/GameProvider.h"

#define PATH_CONFIGURATION "../Configuration.json"


//Sets bullshit of config.json and logger
bool initializeGameConfig(int argc, char* args[]) {

    ConfigurationHandler *configurationHandler = new ConfigurationHandler();
    configurationHandler->loadFileConfiguration(PATH_CONFIGURATION);

    switch (argc){
        case 1:
            configurationHandler->setLogLevel();
            break;
        case 2:
            if (!(Logger::getInstance()->setLevel(args[1]))){
                cout << "Verifique que haya escrito los parametros correctamente." << endl;
                return false;
            } 
            break;
        default:
            cout << "Verifique los parametros, no se permite mas de uno." << endl;
            return false;
    }

    configurationHandler->initializeData();
    GameProvider::setConfig(configurationHandler);
    return true;
}

int main(int argc, char *args[]) {
    if (!initializeGameConfig(argc, args)){
        return EXIT_FAILURE;
    }

    Logger::getInstance()->log(INFO, "Juego iniciado");

    Game *game = new Game();

    game->run();

    //game->~Game();

    //GameProvider::getConfig()->~ConfigurationHandler();

    Logger::getInstance()->log(INFO, "Juego Finalizado");

    return EXIT_SUCCESS;
}