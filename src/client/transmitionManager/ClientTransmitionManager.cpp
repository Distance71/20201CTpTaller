#include "ClientTransmitionManager.h"

/*Consructor and destructor */
ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->clientOwn_ = client;
    this->socket_ = new Socket();
    this->socket_ -> setPort(port);
    this->deserializer_ = new MessageDeserializer();
}


ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
}



/* Sending messages */

void ClientTransmitionManager::sendMessage(Message* message){
    queueSendMessages_->push_back(message);
}


/*static void* _sendMessages(void *arg){
    ClientTransmitionManager *client_transmition_manager = (ClientTransmitionManager *) arg;
    client_transmition_manager->sendMessages();
}*/


// void ClientTransmitionManager::sendMessages(){
//     while (clientOwn_->isConnected()){
//         if (!queueSendMessages_->empty()){
//             Message *message = queueSendMessages_ -> front();
//             queueSendMessages_->erase(queueSendMessages_->begin(),queueSendMessages_->begin()+1);
//             string data = message->getStringData();
//             delete message;
//             socket_->sendMessage(data.c_str(), sizeof(char) *data.size());
//         }
//     }
// }




/* Receiving messages */
static void* _receiveMessages(void *arg){
    ClientTransmitionManager *client_transmition_manager = (ClientTransmitionManager *) arg;
    client_transmition_manager->receiveMessages();
}


void ClientTransmitionManager::receiveMessages(){
}




/*Processing messages*/
static void* _processMessages(void *arg){
    ClientTransmitionManager *client_transmition_manager = (ClientTransmitionManager *) arg;
    client_transmition_manager->processMessages();
}


void ClientTransmitionManager::processMessages(){
}




/* Server conection and threads creation*/
bool ClientTransmitionManager::connectWithServer(string ipAddress){

    if(!this->socket_->create()){
        string errorMessage = "No se pudo crear el socket para conectarse con el server";
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
    
    /*pthread_t sending_thread;
    pthread_create(&sending_thread, NULL,_receiveMessages,this);

    pthread_t receiving_thread;
    pthread_create(&receiving_thread, NULL,_sendMessages,this);

    pthread_t processing_thread;
    pthread_create(&processing_thread, NULL,_processMessages,this);*/
    
    return true;
};




/*Common*/




//-------------------------------------------------------------------------------------------------------
/*static void* sendMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> *queueMessage = transmitionManager->getSendMessages();

    bool error = false;

    while (client->isConnected() && !error){

        if (!queueMessage->empty()){
            Message *newMessage = queueMessage->front();
            queueMessage->erase(queueMessage->begin(), queueMessage->begin() + 1);
            
            string dataSend = newMessage->getStringData();
            //delete newMessage;
            socket->sendMessage(dataSend.c_str(), sizeof(char) *dataSend.size());
        }
    }
}
*/


/*static void* receiveMessage(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer *deserializer = transmitionManager->getDeserializer();
    vector<Message *> *queueMessage = transmitionManager->getReceivedMessages();

    bool error = false;

    while (client->isConnected() && !error){
        // TODO: descomentado por queueMessage: cambiar de vector<Message *>* a EventsQueue*
        //deserializer->pushNewMessage(socket, error, queueMessage);

        // TODO: usleep de prueba
        usleep(1000000);
    }

}*/















Client *ClientTransmitionManager::getClient(){
    return clientOwn_;
};

Socket *ClientTransmitionManager::getSocket(){
    return socket_;
};

vector<Message *> *ClientTransmitionManager::getReceivedMessages(){
    return queueReceiveMessage_;
};

vector<Message *> *ClientTransmitionManager::getSendMessages(){
    return queueSendMessages_;
};

MessageDeserializer *ClientTransmitionManager::getDeserializer(){
    return deserializer_;
};

/*void ClientTransmitionManager::processMessages(){

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

};*/

// void ClientTransmitionManager::processInitEntity(MessageInitEntity *initEntity){

// };

// void ClientTransmitionManager::processInitLayer(MessageInitLayer *initLayer){

//     size_t idLayer = initLayer->getIdLayer();
//     string sourceLayer = initLayer->getSource();

// };

//void ClientTransmitionManager::processGameInit(MessageGameInit *initScreen){

//     unsigned int width = initScreen->getWidth();
//     unsigned int  height = initScreen->getHeight();
//     GameProvider::setWidth(width);
//     GameProvider::setHeight(height);
//     this->clientOwn_->getGameScreen()->initializeGraphics();
//     this->clientOwn_->getGameScreen()->viewLogin();
// };

// void ClientTransmitionManager::processRequestLoginPlayer(MessageRequestLoginPlayer *requestLogin){

// };

// void ClientTransmitionManager::processUpdateEntity(MessageUpdateEntity *updateEntity){

// };

// void ClientTransmitionManager::processUpdateStage(MessageUpdateStage *updateStage){

//     level_t oneLevel = updateStage->getLevel();
    
//     if (updateStage->getIsStartStage()){
//         this->clientOwn_->getGameScreen()->viewStartStage(oneLevel);
//     }

//     if (updateStage->getIsEndStage()){
//         this->clientOwn_->getGameScreen()->viewStageCleared(oneLevel);
//     }
// };

/*void ClientTransmitionManager::sendMovement(orientation_t moveOrientation){
    MessageMovementPlayer *messageMovement = new MessageMovementPlayer(moveOrientation);
    this->queueSendMessage_.push_back(messageMovement);
};*/







/*bool ClientTransmitionManager::getRequestloginPlayerResponse(){
    //TODO hacer algo
    return true;  
};*/