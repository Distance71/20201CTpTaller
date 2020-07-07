#include "ClientTransmitionManager.h"
#include <stdio.h>


ClientTransmitionManager::ClientTransmitionManager(Client *client, size_t port){
    this->client_ = client;
    this->socket_ = new Socket();
    this->socket_-> setPort(port);
    this->deserializer_= new MessageDeserializer();
    sendMessagesQueue_ = new BlockingQueue<Message*>();
}


ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
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


BlockingQueue<Message*> *ClientTransmitionManager::getSendMessagesQueue(){
    return this->sendMessagesQueue_;
};


MessageDeserializer *ClientTransmitionManager::getDeserializer(){
    return this->deserializer_;
};


static void* sendMessages(void *arg){
   ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    BlockingQueue<Message*> *messagesQueue = transmitionManager->getSendMessagesQueue();

    while (client->isConnected()){
        if (!(messagesQueue->empty())){
            Message *newMessage = *messagesQueue->pop(); 

            size_t messageSize = sizeof(*newMessage);
            void *messageRef = &messageSize;
          
            socket->sendMessage((void *&) messageRef, sizeof(size_t));
            socket->sendMessage((void *&) newMessage, messageSize);
        }
    }
    return nullptr;
}


static void* receiveMessages(void *arg){
    Logger::getInstance()->log(DEBUG, "Se creo el hilo de recepcion");
    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    ClientEventsManager* eventsManager = client->getEventsManager();
    MessageDeserializer* deserealizer = transmitionManager->getDeserializer();
    Socket *socket = transmitionManager->getSocket();

    while (client->isConnected()){
        Event* event;
        if (deserealizer->getReceivedMessage(socket,event).ok){
            cout << "Se recibio" << endl;
            //eventsManager->pushBackEvent(event);
        }
    }

    cout << "Se cerro hilo"<< endl;
    Logger::getInstance()->log(DEBUG, "Se cerro el hilo de recepcion");
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
    // pthread_t sending_thread;
    // pthread_create(&sending_thread,NULL,sendMessages,this);

    pthread_t receiving_thread;
    pthread_create(&receiving_thread, NULL,receiveMessages,this);
}