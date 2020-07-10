#include "ClientTransmitionManager.h"

ClientTransmitionManager::ClientTransmitionManager(Client *client){
    this->clientOwn_ = client;
    this->socket_ = new Socket();
    this->socket_-> setPort(client->getPort());
    sendMessagesQueue_ = new BlockingQueue<Message*>();

}


ClientTransmitionManager::~ClientTransmitionManager(){
    delete this->socket_;
    //delete this->sendMessagesQueue_;
}


bool ClientTransmitionManager::connectWithServer(){

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

    if (!this->socket_->connectWithServer(this->clientOwn_->getIpHost())){
        string errorMessage = "No se pudo conectar el cliente con el servidor.";
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return false;
    }

    return true;
}


static void* sendMessages(void *arg){
   /*ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    Socket *socket = transmitionManager->getSocket();
    BlockingQueue<Message*> *messagesQueue = transmitionManager->getSendMessagesQueue();

    while (client->isConnected()){
        if (!(messagesQueue->empty())){
            Message *newMessage = *messagesQueue->pop(); 

            size_t messageSize = sizeof(*newMessage);
            void *messageRef = &messageSize;
          
            //socket->sendMessage((void *&) messageRef, sizeof(size_t));
            //socket->sendMessage((void *&) newMessage, messageSize);
        }
    }*/
    return nullptr;
}


static void* receiveMessages(void *arg){
    /*Logger::getInstance()->log(DEBUG, "Se creo el hilo de recepcion");
    ClientTransmitionManager *transmitionManager = (ClientTransmitionManager *) arg;

    Client *client = transmitionManager->getClient();
    ClientEventsManager* eventsManager = client->getEventsManager();
    
    Socket *socket = transmitionManager->getSocket();
    MessageDeserealizer deserealizer = new MessageDeserealizer();

    while (client->isConnected()){
        Event* event;
        if (deserealizer->getReceivedMessage(socket,event).ok){
            cout << "Se recibio" << endl;
            //eventsManager->pushBackEvent(event);
        }
    }

    cout << "Se cerro hilo"<< endl;
    Logger::getInstance()->log(DEBUG, "Se cerro el hilo de recepcion");*/
    return nullptr;
 }


void ClientTransmitionManager::runThreads(){
    Logger::getInstance()->log(DEBUG, "Se inicializan hilos de envío y recepción de mensajes");
    
    pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);

    pthread_t receiving_thread;
    pthread_create(&receiving_thread, NULL,receiveMessages,this);
}


void ClientTransmitionManager::sendMessage(Message* message){
    //this->sendMessagesQueue_->push(message); //esto rompe
    //Logger::getInstance()->log(DEBUG, "Se agrega mensaje a la cola de salida");
}