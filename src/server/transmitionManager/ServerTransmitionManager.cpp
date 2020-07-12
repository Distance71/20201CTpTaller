#include "ServerTransmitionManager.h"

ServerTransmitionManager::ServerTransmitionManager(Server *server){
    this->serverOwn_ = server;
    //receivedMessagesQueue_ = new BlockingQueue <Message*>();
}

ServerTransmitionManager::~ServerTransmitionManager(){
    //delete this->receivedMessagesQueue_;
}

void ServerTransmitionManager::addUser(User* user){
    //this->createReceivingCycle(user);
    this->createSendingCycle(user);
}

void ServerTransmitionManager::createReceivingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;
    
    args.handler = (void *) this;
    args.params = user; 

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args)->void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        return handler->receivingCycle(user);
    }, (void *) &args);


    //Not handled
    if(pthreadCreateStatus != 0) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario" + to_string(user->getId());
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision receptor.");
}

void* ServerTransmitionManager::receivingCycle(User* user){
    Logger::getInstance()->log(DEBUG, "Se va iniciar el ciclo del receptor transmitionManager");
    
    if(!user || !this->serverOwn_)
        cout << "algo esta mal" << endl;
        
    while (user->isConnected() && this->serverOwn_->isConnected()) {
        Logger::getInstance()->log(DEBUG, "Se va a recibir un evento en transmitionManager");
        Event *event = user->receiveMessage();
        if(!event){
            mtxErrno.lock();
            if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
                Logger::getInstance()->log(DEBUG, "Se detecta desconexión del cliente."+ to_string(user->getId()));
                user->setDisconnection();
                return nullptr;
            }
            mtxErrno.unlock();
            Logger::getInstance()->log(ERROR, "Se ha recibido un evento invalido. Se cerrará la conexión con el cliente");
            return nullptr;
        }
        Logger::getInstance()->log(DEBUG, "Se recibio un evento");
        cout << "se recibio un mensaje" << endl;
        receivedEventQueue_->push(event);        
    }
    
    Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente " + to_string(user->getId()));
    return nullptr;
}



// BlockingQueue<Message *>* ServerTransmitionManager::getMessagesToProcess(){
//     return this->receivedMessagesQueue_;
// }

void ServerTransmitionManager::createSendingCycle(User* user) {
    pthread_t thread;

    argsThread_t args;

    args.handler = (void *) this;
    args.params = user;

    int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args) -> void * {
        auto arguments = (argsThread_t *) args;
        auto *handler = (ServerTransmitionManager *) arguments->handler;
        auto *user = (User *) arguments->params;

        return handler->sendingCycle(user);
    }, (void *) &args);

    if(pthreadCreateStatus != 0) {
        string errorMessage = "No se pudo crear el hilo para manejar el receptor de mensajes para el usuario" + to_string(user->getId());
        Logger::getInstance()->log(ERROR, errorMessage);
        GameProvider::setErrorStatus(errorMessage);
        return;
    }

    Logger::getInstance()->log(DEBUG, "Se creó el hilo de transmision emisor.");
}



void* ServerTransmitionManager::sendingCycle(User* user) {
    
    //while(user->isConnected() && this->serverOwn_->isConnected()){
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));

        Event* event11 = new EventResponseLoginPlayer(ERROR_WRONG_CREDENTIALS);
        response_t response11 = user->sendMessage(event11);

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        Event* event12 = new EventResponseLoginPlayer(ERROR_FULL_GAME);
        response_t response12 = user->sendMessage(event12);

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        Event* event13 = new EventResponseLoginPlayer(OK);
        response_t response13 = user->sendMessage(event13);

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        screen_t screenSize;
        screenSize.height = 800;
        screenSize.width = 1280;
        Event* event2 = new EventGameInit(screenSize);
        response_t response2 = user->sendMessage(event2);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1412));

        char path1[100];
        strcpy(path1, "assets/TransitionScreens/Stage1.JPG");
        Event* event3 = new EventAnimationInitStage(path1);
        response_t response3 = user->sendMessage(event3);

        std::this_thread::sleep_for(std::chrono::milliseconds(2500));

        char layerPaths[7][100];
        strcpy(layerPaths[0], "assets/Stage/Level1/layer_1.png");
        strcpy(layerPaths[1], "assets/Stage/Level1/layer_2.png");
        strcpy(layerPaths[2], "assets/Stage/Level1/layer_3.png");
        strcpy(layerPaths[3], "assets/Stage/Level1/layer_4.png");
        strcpy(layerPaths[4], "assets/Stage/Level1/layer_5.png");
        strcpy(layerPaths[5], "");
        strcpy(layerPaths[6], "");
        Event* event4 = new EventInitStage(layerPaths);
        response_t response5 = user->sendMessage(event4);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        char path2[100];
        strcpy(path2, "assets/TransitionScreens/Stage1Cleared");
        Event* event5 = new EventEndStage(path2);



        // response_t response4 = user->sendMessage(event5);

        // while(true){

        //     while(0 >= (ms - elaptedTimeMS)) { 
        //         end = chrono::high_resolution_clock::now();
        //         dur = end - begin;
        //         ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        //     }
        // }


        
        //response = user->sendMessage(event);

        // if(response.ok)
        //     cout << "Se mando ok" << endl;

        
    //     return nullptr;
        //return nullptr;
    //}
    return nullptr;
}

void ServerTransmitionManager::sendToUser(Id idUser){

}

void ServerTransmitionManager::sendToAllUsers(Event *event){

}
