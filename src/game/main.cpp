#include "models/Game.h"
#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "../providers/GameProvider.h"

#define PATH_CONFIGURATION "../Configuration.json"


//Sets bullshit of config.json and logger
bool initializeGameConfig(int argc, char* args[]) {
    ConfigurationHandler::getInstance()->loadFileConfiguration(PATH_CONFIGURATION);

    switch (argc){
        case 1:
            ConfigurationHandler::getInstance()->setLogLevel();
            break;
        case 2:
            Logger::getInstance()->setLevel(args[1]);
            break;
        default:
            cout << "Verifique que haya escrito los parametros correctamente." << endl;
            return false;
    }

    ConfigurationHandler::getInstance()->initializeData();
    return true;
}

int main(int argc, char *args[]) {
    if (!initializeGameConfig(argc, args)){
        return EXIT_FAILURE;
    }

    Logger::getInstance()->log(INFO, "Juego iniciado");
    Game game;

    game.run();

    game.~Game();
    
    return EXIT_SUCCESS;
}