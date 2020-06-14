#include "Server.h"

Server::Server(size_t port){
    this->port_ = port;
    this->maxPlayers = 0;
    this->socket_ = new Socket(port);
    this->connected_ = false;
}

Server::~Server(){
    this->socket_->cerrar();
    //delete this->socket_;

    Logger::getInstance()->log(INFO, "Fin del juego");
}

//Pre: 
void Server::initializeServer() {

    if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket para recibir clientes en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    if(!this->socket_->setOption()){
        string errorMessage = "No se pudieron setear las opciones del socket en el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    if (!this->socket_->enlazar()) {
        string errorMessage = "No se pudo asignar una direccion al socket del server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->maxPlayers = GameProvider::getQuantityPlayers();

    if(!this->socket_->escuchar(this->maxPlayers)) {
        string errorMessage = "No se pudo configurar el socket para aceptar configuraciones entrantes";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    this->connected_ = true;
    Logger::getInstance()->log(INFO, "Se creo el socket con exito");
    cout << "Se crea servidor escuchando el puerto " + to_string(this->port_) << endl;
}

bool Server::isConnected(){
    return this->connected_;
}

bool Server::waitPlayers(){
    cout << "Esperando jugadores..." << endl;

    while (this->maxPlayers > this->players.size()){
    
        int newClient = this->socket_->acceptClient();

        if (newClient < 0){
            cout << "Error al aceptar cliente" << endl;
        } else {
            this->players.push_back(newClient);

            cout << "Se agrega el cliente " + to_string(this->players.size()) << endl;

            /*
            pthread_t newHilo;

            argpthread argumentos;
            argumentos.server = this;
            argumentos.nroClient = this->clients.size();
            argumentos.des = this->deserializer;

            pthread_create(&newHilo, NULL, recibirInformacion, &argumentos);*/

        }
    }
}

int Server::run(){
    this->initializeServer();

    if(!this->isConnected())
        return EXIT_FAILURE;

    if(!this->waitPlayers())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}