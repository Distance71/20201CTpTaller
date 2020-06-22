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

        // TODO: usleep de prueba
        usleep(1000000);
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

void ClientTransmitionManager::processMessages(){

    while (this->clientOwn_->isConnected()){

        if (!this->queueReceiveMessage_.empty()){
            Message *newMessage = this->queueReceiveMessage_.front();
            this->queueReceiveMessage_.erase(this->queueReceiveMessage_.begin(), this->queueReceiveMessage_.begin() + 1);

            switch (newMessage->getType()){
                
                case INIT_SCREEN:
                    this->processInitScreen((MessageInitScreen *) newMessage);
                    break;
                case INIT_ENTITY:
                    this->processInitEntity((MessageInitEntity *) newMessage);
                    break;

                case UPDATE_ENTITY:
                    this->processUpdateEntity((MessageUpdateEntity *) newMessage);
                    break;

                case INIT_LAYER:
                    this->processInitLayer((MessageInitLayer *) newMessage);
                    break;

                case UPDATE_STAGE:
                    this->processUpdateStage((MessageUpdateStage *) newMessage);
                    break;

                case REQUEST_LOGIN_PLAYER:
                    this->processRequestLoginPlayer((MessageRequestLoginPlayer *) newMessage);
                    break;
                
                case NONE:
                default:
                    break;
            }
        }

        // TODO: usleep de prueba
        usleep(10000000);
    }

};

void ClientTransmitionManager::processInitEntity(MessageInitEntity *initEntity){

};

void ClientTransmitionManager::processInitLayer(MessageInitLayer *initLayer){

};

void ClientTransmitionManager::processInitScreen(MessageInitScreen *initScreen){

    unsigned int width = initScreen->getWidth();
    unsigned int  height = initScreen->getHeight();
    GameProvider::setWidth(width);
    GameProvider::setHeight(height);
    this->clientOwn_->getGameScreen()->initializeGraphics();
    this->clientOwn_->getGameScreen()->viewLogin();
};

void ClientTransmitionManager::processRequestLoginPlayer(MessageRequestLoginPlayer *requestLogin){

};

void ClientTransmitionManager::processUpdateEntity(MessageUpdateEntity *updateEntity){

};

void ClientTransmitionManager::processUpdateStage(MessageUpdateStage *updateStage){

    level_t oneLevel = updateStage->getLevel();
    
    if (updateStage->getIsStartStage()){
        this->clientOwn_->getGameScreen()->viewStartStage(oneLevel);
    }

    if (updateStage->getIsEndStage()){
        this->clientOwn_->getGameScreen()->viewStageCleared(oneLevel);
    }
};

