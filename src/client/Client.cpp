#include "Client.h"

Client::Client(string ipAddress, size_t port){
    this->name_ = "";
    this->ipHost_ = ipAddress;
    this->port_ = port;
    this->socket_ = new Socket(port);
    this->gameScreen_ = new GameScreen(this);
}

Client::~Client(){
    delete this->gameScreen_;
}

void Client::initializeClient(){

    if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket conectarse con el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    if(!this->socket_->setOption()){
        string errorMessage = "No se pudieron setear las opciones del socket en el cliente";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    if (!this->socket_->connectWithServer(this->ipHost_)){
        string errorMessage = "No se pudo conectar el cliente con el servidor.";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        this->connected_ = false;
        return;
    }

    this->connected_ = true;
    Logger::getInstance()->log(INFO, "Se creo el socket con exito. Se conecta el cliente con host " + this->ipHost_ + " y puerto " + to_string(this->port_));

}

int Client::run(){

    this->initializeClient();

    if (!this->isConnected())
        return EXIT_FAILURE;

    cout << "Se Conectado con el servidor " << endl;
     
    if (!this->gameScreen_->viewLogin())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;    
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