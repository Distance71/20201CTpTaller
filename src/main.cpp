#include "../services/Logger.h"
#include "../services/ConfigurationHandler.h"
#include "../providers/GameProvider.h"

#include <iostream>
#include <getopt.h>

#define PATH_CONFIGURATION "../Configuration.json"
#define INDEX_MODE 1

void showHelp(){
    cout << "Uso: ejemplo [opcion]..." << endl;
    cout << "Opciones:" << endl;
    cout << "\t --help \t Ver esta ayuda" << endl;
    cout << "\t -l \t" << endl;
    cout << "\t --log \t \t Establecer nivel de log" << endl;
    cout << "\t -c file \t" << endl;
    cout << "\t --config=file \t Establecer archivo de configuracion" << endl;
}

//Rewrite depending on server/client
void initializeGameConfig(string pathConfiguration, string levelLog){

    ConfigurationHandler *configurationHandler = new ConfigurationHandler();

    try {
        configurationHandler->loadFileConfiguration(pathConfiguration); 
    } catch (invalid_argument &e){
        Logger::getInstance()->log(ERROR, "Error sintactico en archivo de configuracion (" + string(e.what()) + "). Se procede a cargar el archivo de default.");
        configurationHandler->setConfigDefault();
    }

    if (levelLog == ""){
        configurationHandler->setLogLevel();
    } else {
        Logger::getInstance()->setLevel(levelLog);
    }

    configurationHandler->initializeData();
    GameProvider::setConfig(configurationHandler);
}

int main(int argc, char *args[]) {

    const char* const short_opts = "hl:c:";
    const option long_opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"log", required_argument, NULL, 'l'},
        {"config", required_argument, NULL, 'c'},
        {NULL, 0, NULL, 0}
    };

    int opt;
    std::string levelLog, pathConfig;

    while ((opt = getopt_long(argc, args, short_opts, long_opts, nullptr)) != -1){
        switch (opt) {
            case 'h':
                showHelp();
                return EXIT_SUCCESS;
            case 'c':
                pathConfig = optarg;
                break;
            case 'l':
                levelLog = optarg;
                break;
            
            default:
                showHelp();
                return EXIT_FAILURE;
        }
    }

    initializeGameConfig(pathConfig, levelLog);

    Logger::getInstance()->log(INFO, "Juego iniciado");

    switch(str2int(args[INDEX_MODE])) {
        case str2int("SERVER"):
            Server *server = new Server();
            server->run();
            break;        

        case str2int("CLIENT"):
            Client *client = new Client();
            client->run();
            break;

        default:;
            cout << "Ha Ejecutado mal el modo de la aplicacion" << endl;
            return EXIT_FAILURE;
    }   

    //Game *game = new Game();

    //game->run();

    Logger::getInstance()->log(INFO, "Juego Finalizado");

    return EXIT_SUCCESS;
}