#include "Game.h"
#include "../services/Logger.h"
#include "../providers/GameProvider.h"


//Sets bullshit of config.json and logger
void initializeGameConfig(int argc, char* args[]) {

}

int main(int argc, char *args[]) {

    //Call initializeGameConfig

    GameProvider::getLogger()->log(INFO, "Juego iniciado");

    Game game;

    game.loop();

    return EXIT_SUCCESS;
}