#include "ClientTransmitionManager.h"

ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->client_ = client;
    this->socket_ = new Socket();
    this->socket_-> setPort(port);
    this->deserializer_= new MessageDeserializer();
    this->serializer_ = new MessageSerializer();
    sendMessagesQueue_ = new BlockingQueue<Message*>();
}

ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
    delete this->sendMessagesQueue_;
}


void ClientTransmitionManager::sendMessage(Message* message){
    this->sendMessagesQueue_->push(message); 
}


Client *ClientTransmitionManager::getClient(){
    return this->client_;
};


Socket *ClientTransmitionManager::getSocket(){
    return this->socket_;
};

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

    return true;
}


static void* sendMessages(void *arg){

    Logger::getInstance()->log(DEBUG, "Se crea el hilo de envío de mensajes");
    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;
    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    BlockingQueue<Message*> *messagesQueue = transmitionManager->getSendMessagesQueue();

    while (client->isConnected()){
        if (!(messagesQueue->empty())){
            Message *message = messagesQueue->pop(); 
            transmitionManager->sendSerializedMessage(message);
            Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje en TransmitionManager");
        }
    }
    
    Logger::getInstance()->log(DEBUG, "Se cerró el hilo de envío de mensajes");
    return nullptr;
}

void ClientTransmitionManager::sendSerializedMessage(Message* message){
    this->serializer_->sendSerializedEvent(this->socket_, message);
}


static void* receiveMessages(void *arg){
    Logger::getInstance()->log(DEBUG, "Se creo el hilo de recepcion de mensajes");
    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;
    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    MessageDeserializer deserealizer = MessageDeserializer();

    while (client->isConnected()){
        Event* event;
        response_t response = deserealizer.getReceivedMessage(socket,event); 
        if (response.status == DISCONNECTION || response.status==ERROR_CONNECTION) {
            Logger::getInstance()->log(INFO, "Se detecta desconexión del cliente.");
            Logger::getInstance()->log(DEBUG, "Se detiene el hilo de recepción para un usuario");
            client->ServerDisconnection();
            return nullptr;
        }
        else if (response.ok){
            Logger::getInstance()->log(DEBUG, "Se recibio ok un evento en transmitionManager");
            client->processEvent(event);

        }
        else{
            Logger::getInstance()->log(ERROR, "Error al recibir el mensaje");
        }
    }
    
    Logger::getInstance()->log(DEBUG, "Se cerro el hilo de recepcion");
    return nullptr;
 }


void ClientTransmitionManager::run(){
    Logger::getInstance()->log(DEBUG, "Se inicializan hilos de envío y recepción de mensajes");
    
    pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);

    pthread_t receiving_thread;
    pthread_create(&receiving_thread, NULL,receiveMessages,this);
}

BlockingQueue<Message*> *ClientTransmitionManager::getSendMessagesQueue(){
    return this->sendMessagesQueue_;
}