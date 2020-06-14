#include "ClientTransmitionManager.h"


static void* sendMessage(void *arg){

}

static void* receiveMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> queueMessage = transmitionManager->getMessages();

    bool error = false;

    while (client->isConnected() && !error){

        Message *newMessage = deserializer->getReceivedMessage(socket, error);

    }

}

ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->clientOwn_ = client;
    this->socket_ = new Socket();
    this->socket_->setPort(port);

    this->deserializer_ = new MessageDeserializer();
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

Client *ClientTransmitionManager::getClient(){
    return this->clientOwn_;
};

Socket *ClientTransmitionManager::getSocket(){
    return this->socket_;
};

vector<Message *> ClientTransmitionManager::getMessages(){
    return this->queueMessage_;
};

MessageDeserializer *ClientTransmitionManager::getDeserializer(){
    return this->deserializer_;
};
