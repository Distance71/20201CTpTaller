#include "Client.h"

Client::Client(string ipAddress, size_t port){
    this->name_ = "";
    this->ipHost_ = ipAddress;
    this->port_ = port;
}

Client::~Client(){}

void Client::initializeClient(){

    sockaddr_in serverAddr{};
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(this->ipHost_.c_str());
    serverAddr.sin_port = htons(this->port_);

    Logger::getInstance()->log(DEBUG, "Se conecta el cliente con host" + this->ipHost_ + " y puerto " + to_string(this->port_));

    this->socket_ = socket(AF_INET, SOCK_STREAM, 0);

    if(this->socket_ < 0){
        string errorMessage = "No se pudo crear el socket conectarse con el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    int enable = 1;
    int optsSetted = (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0);

    if(optsSetted < 0){
        string errorMessage = "No se pudieron setear las opciones del socket en el cliente";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    if (connect(this->socket_, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        string errorMessage = "No se pudo conectar el cliente con el servidor.";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    this->connected_ = true;
    Logger::getInstance()->log(DEBUG, "Se creo el socket con exito");
}

int Client::run(){

    this->initializeClient();

    if (!this->isConnected())
        return EXIT_FAILURE;
    
}

bool Client::isConnected(){
    return this->connected_;
}

void Client::disconnect(){
    this->connected_ = false;

    // Cerrar conexiones, socket, logger situacion...
}

void Client::setName(string oneName){
    this->name_ = oneName;
}

string Client::getName(){
    return this->name_;
}