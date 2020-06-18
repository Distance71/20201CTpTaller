#include "ClientTransmitionManager.h"


static void* sendMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> *queueMessage = transmitionManager->getSendMessages();

    bool error = false;

    while (client->isConnected() && !error){

        if (!queueMessage->empty()){
            // Secuencia de sacar un mensaje y enviarlo
        }
    }
}

static void* receiveMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> *queueMessage = transmitionManager->getReceivedMessages();

    bool error = false;

    while (client->isConnected() && !error){

        deserializer->pushNewMessage(socket, error, queueMessage);
        Message *newMessage = queueMessage->at(0);
        
        switch (newMessage->getType()){
            case INIT_SCREEN:
                {
                    MessageInitScreen *initScreen = (MessageInitScreen *) newMessage;
                    unsigned int width = initScreen->getWidth();
                    unsigned int  height = initScreen->getHeight();
                    GameProvider::setWidth(width);
                    GameProvider::setHeight(height);
                    client->getGameScreen()->initializeGraphics();
                    client->getGameScreen()->viewLogin();
                    break;
                }
            case INIT_ENTITY:
                break;

            case UPDATE_ENTITY:
                break;

            case INIT_LAYER:
                break;

            case UPDATE_STAGE:
                break;

            case REQUEST_LOGIN_PLAYER:
                break;
              
            case NONE:
            default:
                break;
        }

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
    
    pthread_t newHilo;
    pthread_create(&newHilo, NULL, receiveMessage, this);

    return true;
};

Client *ClientTransmitionManager::getClient(){
    return this->clientOwn_;
};

Socket *ClientTransmitionManager::getSocket(){
    return this->socket_;
};

vector<Message *> *ClientTransmitionManager::getReceivedMessages(){
    return &this->queueReceiveMessage_;
};

vector<Message *> *ClientTransmitionManager::getSendMessages(){
    return &this->queueSendMessage_;
};

MessageDeserializer *ClientTransmitionManager::getDeserializer(){
    return this->deserializer_;
};
