#include "ClientTransmitionManager.h"
#include <stdio.h>


ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->client_ = client;
    this->socket_ = new Socket();
    this->socket_-> setPort(port);
    this->deserializer_= new MessageDeserializer();
    sendMessagesQueue_ = new vector <Message*>;
}


ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
}


void ClientTransmitionManager::sendMessage(Message* message){
    this->sendMessagesQueue_->push_back(message);
}


Client *ClientTransmitionManager::getClient(){
    return this->client_;
};


Socket *ClientTransmitionManager::getSocket(){
    return this->socket_;
};


vector<Message * >*ClientTransmitionManager::getSendMessagesQueue(){
    return this->sendMessagesQueue_;
};


MessageDeserializer *ClientTransmitionManager::getDeserializer(){
    return this->deserializer_;
};


static void* sendMessages(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    vector<Message *> *MessagesQueue = transmitionManager->getSendMessagesQueue();

    bool error = false;
    while (client->isConnected() && !error){

        if (!(MessagesQueue->empty())){
            Message *newMessage = MessagesQueue->front();
            MessagesQueue->erase(MessagesQueue->begin(), MessagesQueue->begin() + 1); 

            size_t messageSize = sizeof(*newMessage);
           // const void*& _messageSize = (const void *) &messageSize;
            socket->sendMessage((const void *&) messageSize, sizeof(size_t));
            socket->sendMessage((const void *&) newMessage, sizeof(*newMessage));
        }
    }
}


static void* receiveMessages(void *arg){

    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    ClientEventsManager* eventsManager = client->getEventsManager();
    MessageDeserializer* deserealizer = transmitionManager->getDeserializer();
    Socket *socket = transmitionManager->getSocket();

    while (client->isConnected()){
        Event* event; //event = deserealizer dame el evento
        //deserealizer->getReceivedMessage(socket, event);
        if (event){
            eventsManager->pushBackEvent(event);
        }
    }
 }


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


void ClientTransmitionManager::run(){
    pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);

    pthread_t receiving_thread;
    pthread_create(&receiving_thread, NULL,receiveMessages,this);
}