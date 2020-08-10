#include "services/Logger.h"
#include "services/ConfigurationHandler.h"
#include "providers/GameProvider.h"

#include <iostream>
#include <getopt.h>
#include <boost/algorithm/string.hpp>
#include "../client/Client.h"
#include "../client/ClientTest.h"
#include "../server/Server.h"

#define INDEX_MODE 1

void showHelpServer(){
    cout << "MODO SERVER:" << endl;
    cout << "\t -p \t" << endl;
    cout << "\t --port \t Puerto a conectarse" << endl;
    cout << "\t -l \t" << endl;
    cout << "\t --log \t \t Establecer nivel de log" << endl;
    cout << "\t -c file \t" << endl;
    cout << "\t --config=file \t Establecer archivo de configuracion" << endl;
}

void showHelpClient(){
    cout << "MODO CLIENT:" << endl;
    cout << "\t -p \t" << endl;
    cout << "\t --port \t Puerto a conectarse" << endl;
    cout << "\t -i \t" << endl;
    cout << "\t --ip \t \t Direccion IP a conectarse" << endl;
    cout << "\t -l \t" << endl;
    cout << "\t --log \t \t Establecer nivel de log" << endl;
    cout << "\t -c file \t" << endl;
    cout << "\t --config=file \t Establecer archivo de configuracion" << endl;
}

void showHelp(){
    cout << "Uso: ejemplo [opcion]..." << endl;
    cout << "Opciones:" << endl;
    cout << "\t -h \t" << endl;
    cout << "\t --help \t Ver esta ayuda" << endl;
    cout << "\t -m \t" << endl;
    cout << "\t --mode \t Modo de la aplicacion (Server / Client)" << endl;

    cout << "" << endl;
    showHelpServer();

    cout << "" << endl;
    showHelpClient();
}

int mainServer(int port, string levelLog, string pathConfiguration){

   if (port < 0){
        cout << "Falta parámetro Port requerido para conectar el servidor." << endl;
        showHelp();
        return EXIT_FAILURE;
    }

    Logger::setTypeInstance("SERVER");
    ConfigurationHandler *configurationHandler = new ConfigurationHandler(true);
    
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

    Server *newServer = new Server(port);
    int codExitServer = newServer->run();
    delete newServer;
    return codExitServer;
}

int mainClient(int port, string ipAddress, string levelLog, string pathConfiguration, bool modeTest=false){

   if (port < 0){
        cout << "Falta parámetro Port requerido para conectar el cliente." << endl;
        showHelp();
        return EXIT_FAILURE;
    } 

    if (ipAddress == ""){
        cout << "Falta dirección IP requerida para conectar el cliente." << endl;
        showHelp();
        return EXIT_FAILURE;
    } 

    ConfigurationHandler *configurationHandler = new ConfigurationHandler(false);

    Logger::setTypeInstance("CLIENT"); 
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

    int codExitClient;

    Client *newClient = new Client(ipAddress, port);
    codExitClient = newClient->run();
    delete newClient;
    delete configurationHandler;
    return codExitClient;
}

int main(int argc, char *argv[]) {

    const char* const short_opts = "m:p:i:hl:c:";
    const option long_opts[] = {
        {"mode", required_argument, NULL, 'm'},
        {"port", required_argument, NULL, 'p'},
        {"ip", required_argument, NULL, 'i'},
        {"help", no_argument, NULL, 'h'},
        {"log", required_argument, NULL, 'l'},
        {"config", required_argument, NULL, 'c'},
        {NULL, 0, NULL, 0}
    };

    int opt;
    int port = -1;
    string modeApp, ipAddress, levelLog, pathConfig;
    
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1){
        switch (opt) {
            case 'm':
                modeApp = optarg;
                break;
            case 'p':
                port = stoi(optarg);
                break;
            case 'i':
                ipAddress = optarg;
                break;
            case 'c':
                pathConfig = optarg;
                break;
            case 'l':
                levelLog = optarg;
                break;
            case 'h':
                showHelp();
                return EXIT_SUCCESS;
            
            default:
                showHelp();
                return EXIT_FAILURE;
        }
    }

    boost::to_upper(modeApp);

    if (modeApp == "SERVER")
        return mainServer(port, levelLog, pathConfig);
   
    if (modeApp == "CLIENT")
        return mainClient(port, ipAddress, levelLog, pathConfig);
    
    if (modeApp == "CLIENT-TEST")
        return mainClient(port, ipAddress, levelLog, pathConfig, true);

    cout << "Modo de juego inválido" << endl;
    showHelp();
    return EXIT_FAILURE;
}