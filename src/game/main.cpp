#include "models/Game.h"
#include "../services/Logger.h"
#include "../services/ParserJson.h"
#include "../providers/GameProvider.h"

#define PATH_CONFIGURATION "../Configuration.json"

//Sets bullshit of config.json and logger
bool initializeGameConfig(int argc, char* args[]) {
    ParserJson *parserJson = new ParserJson();
    parserJson->loadConfiguration(PATH_CONFIGURATION);

    switch (argc){
        case 1:
            parserJson->setLogLevel();
            return true;
        case 2:
            Logger::getInstance()->setLevel(args[1]);
            return true;
        default:
            cout << "Verifique que haya escrito los parametros correctamente." << endl;
            return false;
    }
}

int main(int argc, char *args[]) {

    if (!initializeGameConfig(argc, args)){
        return EXIT_FAILURE;
    }

    Logger::getInstance()->log(INFO, "Juego iniciado");

    Game game;

    game.run();

    return EXIT_SUCCESS;
}