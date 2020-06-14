#include "ClientTransmitionManager.h"

/*
static void* sendMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> queueMessage = transmitionManager->getMessages();

    bool error = false;

    while (client->isConnected() && !error){

        Message *newMessage = deserializer->getReceivedMessage(socket, error);

    }
}*/

/*
static void* receiveMessage(void *arg){

    struct argpthread *argumentos = (struct argpthread *) arg;

    bool clientIsOpen = true;
    int indexClient = argumentos->nroClient - 1;
    Server *self;
    self = argumentos->server;

    Deserializer *deserial;
    deserial = argumentos->des;

    while (clientIsOpen){
        Message *nuevoMensaje;
        nuevoMensaje = deserial->procesarMensaje(self->socket, &self->clients.at(indexClient), clientIsOpen);

        typeMessage_t tipo;
        tipo = nuevoMensaje->getType();
        cout << to_string(tipo) << endl;
    }

}*/

ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->clientOwn_ = client;
    this->socket_ = new Socket();
    this->socket_->setPort(port);

    //this->deserializer_ = new MessageDeserializer();
}

ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
}

bool ClientTransmitionManager::connectWithServer(string ipAddress){

    if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket conectarse con el server";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    if(!this->socket_->setOption()){
        string errorMessage = "No se pudieron setear las opciones del socket en el cliente";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    if (!this->socket_->connectWithServer(ipAddress)){
        string errorMessage = "No se pudo conectar el cliente con el servidor.";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    return true;
};
