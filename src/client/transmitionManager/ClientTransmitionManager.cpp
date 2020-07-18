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
        // if (!(messagesQueue->empty())){
        //     Message *message = messagesQueue->pop(); 
        //     transmitionManager->sendSerializedMessage(message);
        //     cout << "Se va a mandar un mensaje" << endl;
        //     Logger::getInstance()->log(DEBUG, "Se va a enviar un mensaje en TransmitionManager");
        // }
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

    // while (client->isConnected()){
    //     Event* event;
    //     response_t response = deserealizer.getReceivedMessage(socket,event); 
    //     if (response.ok){
    //         Logger::getInstance()->log(DEBUG, "Se recibio ok un evento en transmitionManager");
    //         client->processEvent(event);
    //         cout << "Se recibio" << endl;
    //     }
    //     else{
    //         Logger::getInstance()->log(ERROR, "Error al recibir el mensaje");
    //     }
    // }
    
    // while (client->isConnected()) {

    // }
    //client->processEvent(new EventSceneAnimation(WAITING_PLAYERS));
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    client->processEvent(new EventResponseLoginPlayer(OK));
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    client->processEvent(new EventSceneAnimation(INIT_STAGE_1));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    client->processEvent(new EventSetLevel(LEVEL_ONE));

    position_t positionP1, positionP2, positionP3, positionP4, positionE1, positionE2;
    for(size_t i = 0; i < 1000; i++){
        positionP1.axis_x = 50;
        positionP1.axis_y = 50;
        positionP1.orientation = FRONT;
        positionP2.axis_x = 800;
        positionP2.axis_y = 500;
        positionP2.orientation = BACK;
        positionP3.axis_x = 500;
        positionP3.axis_y = 100;
        positionP3.orientation = FRONT;
        positionP4.axis_x = 300;
        positionP4.axis_y = 550;
        positionP4.orientation = BACK;
        positionE1.axis_x = 800;
        positionE1.axis_y = 800;
        positionE1.orientation = BACK;
        positionE2.axis_x = 1000;
        positionE2.axis_y = 90;
        positionE2.orientation = BACK;
        
        client->processEvent(new EventMapElementUpdate(PLAYER_1, positionP1));
        client->processEvent(new EventMapElementUpdate(PLAYER_2, positionP2));
        client->processEvent(new EventMapElementUpdate(PLAYER_3, positionP3));
        client->processEvent(new EventMapElementUpdate(PLAYER_4, positionP4));
        client->processEvent(new EventMapElementUpdate(PLAYER_4, positionP4));
        client->processEvent(new EventMapElementUpdate(ENEMY_1, positionE1));
        client->processEvent(new EventMapElementUpdate(ENEMY_2, positionE2));

        std::this_thread::sleep_for(std::chrono::milliseconds(16));    
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // client->processEvent(new EventSceneAnimation(END_STAGE_1));
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // client->processEvent(new EventSceneAnimation(INIT_STAGE_2));
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // client->processEvent(new EventSceneAnimation(END_STAGE_2));
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // client->processEvent(new EventSceneAnimation(INIT_STAGE_3));
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // client->processEvent(new EventSceneAnimation(END_STAGE_3));
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // client->processEvent(new EventSceneAnimation(END_GAME_ANIMATION));
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
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