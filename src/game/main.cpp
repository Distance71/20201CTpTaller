#include "models/Game.h"
#include "../services/Logger.h"
#include "../services/ParserJson.h"
#include "../providers/GameProvider.h"

#define PATH_CONFIGURATION "../Configuration.json"

//Sets bullshit of config.json and logger
void initializeGameConfig(int argc, char* args[]) {
    ParserJson *parserJson = new ParserJson();
    parserJson->loadConfiguration(PATH_CONFIGURATION);

    if (argc > 1){
        Logger::getInstance()->setLevel(args[1]);
    } else {
        parserJson->setLogLevel();
    }
}

int main(int argc, char *args[]) {

    initializeGameConfig(argc, args);

    GameProvider::getLogger()->log(INFO, "Juego iniciado");

    Game game;

    game.run();

    return EXIT_SUCCESS;
}