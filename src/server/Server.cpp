#include "Server.h"

Server::Server(){

}

Server::~Server(){
    shutdown(socket_, SHUT_RDWR);
    close(socket_);

    Logger::getInstance()->log(INFO, "Fin del juego");
}

//Pre: 
void Server::initializeServer(size_t port) {
    sockaddr_in serverAddr{};
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_ < 0){
        string errorMessage = "No se pudo crear el socket para recibir clientes en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        setErrorStatus(errorMessage);
        return;
    }

    int enable = 1;
    int optsSetted = setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0);

    if(optsSetted < 0){
        string errorMessage = "No se pudieron setear las opciones del socket en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    int bindStatus = bind(socket_, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (bindStatus < 0) {
        string errorMessage = "No se pudo asignar una direccion al socket del server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    size_t quantityPlayers = GameProvider::getQuantityPlayers();
    int createSocket = listen(socket_, quantityPlayers);

    if(createSocket) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creo el socket con exito");
}

void Server::run(){
    initializeServer(5000); //Change this, as param or send to config



}