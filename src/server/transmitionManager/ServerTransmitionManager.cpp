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
        this->serverOwn_->processEvent(event);        
    }
    
    Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente " + to_string(user->getId()));
    return nullptr;
}

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

        // user->sendMessage(new EventResponseLoginPlayer(ERROR_WRONG_CREDENTIALS));
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        // response_t response12 = user->sendMessage(new EventResponseLoginPlayer(ERROR_FULL_GAME));
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        user->sendMessage(new EventResponseLoginPlayer(OK));
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        screen_t screenSize;
        screenSize.height = 800;
        screenSize.width = 1280;
        response_t response2 = user->sendMessage(new EventGameInit(screenSize));
        std::this_thread::sleep_for(std::chrono::milliseconds(1412));

        char path1[100];
        strcpy(path1, "assets/TransitionScreens/Stage1.JPG");
        user->sendMessage(new EventAnimationInitStage(path1));
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));

        char layerPaths[7][100];
        strcpy(layerPaths[0], "assets/Stage/Level1/layer_1.png");
        strcpy(layerPaths[1], "assets/Stage/Level1/layer_2.png");
        strcpy(layerPaths[2], "assets/Stage/Level1/layer_3.png");
        strcpy(layerPaths[3], "assets/Stage/Level1/layer_4.png");
        strcpy(layerPaths[4], "assets/Stage/Level1/layer_5.png");
        strcpy(layerPaths[5], "");
        strcpy(layerPaths[6], "");
        user->sendMessage(new EventInitStage(layerPaths));        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        char pathElement1[100];
        strcpy(pathElement1, "assets/Enemies/enemigo1.png");
        position_t position1;
        spriteSize_t spriteSize1;
        spriteSize1.width = 200;
        spriteSize1.height = 200;

        for(size_t i = 0; i < 100; i++){
            size_t id1 = i;
            position1.axis_x = rand() % 1200;
            position1.axis_y = rand() % 800;    
            position1.orientation = FRONT;
            user->sendMessage(new EventMapElementCreate(id1, pathElement1, position1, spriteSize1)); 
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        // user->sendMessage(new EventMapElementUpdate(id1, position1));
        // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        // user->sendMessage(new EventMapElementDelete(id1));

        //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        // char path2[100];
        // strcpy(path2, "assets/TransitionScreens/Stage1Cleared.JPG");
        // user->sendMessage(new EventEndStage(path2));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // char path3[100];
        // strcpy(path3, "assets/TransitionScreens/Stage2.JPG");
        // user->sendMessage(new EventAnimationInitStage(path3));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2500));

        // char layerPaths2[7][100];
        // strcpy(layerPaths2[0], "assets/Stage/Level2/layer_1.png");
        // strcpy(layerPaths2[1], "assets/Stage/Level2/layer_2.png");
        // strcpy(layerPaths2[2], "assets/Stage/Level2/layer_3.png");
        // strcpy(layerPaths2[3], "assets/Stage/Level2/layer_4.png");
        // strcpy(layerPaths2[4], "assets/Stage/Level2/layer_5.png");
        // strcpy(layerPaths2[5], "assets/Stage/Level2/layer_6.png");
        // strcpy(layerPaths2[6], "assets/Stage/Level2/layer_7.png");
        // user->sendMessage(new EventInitStage(layerPaths2));        
        // std::this_thread::sleep_for(std::chrono::milliseconds(4000));

        // char path4[100];
        // strcpy(path4, "assets/TransitionScreens/Stage2Cleared.JPG");
        // user->sendMessage(new EventEndStage(path4));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // char path5[100];
        // strcpy(path5, "assets/TransitionScreens/Stage3.JPG");
        // user->sendMessage(new EventAnimationInitStage(path5));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2500));

        // char layerPaths3[7][100];
        // strcpy(layerPaths3[0], "assets/Stage/Level3/layer_1.png");
        // strcpy(layerPaths3[1], "assets/Stage/Level3/layer_2.png");
        // strcpy(layerPaths3[2], "assets/Stage/Level3/layer_3.png");
        // strcpy(layerPaths3[3], "assets/Stage/Level3/layer_4.png");
        // strcpy(layerPaths3[4], "assets/Stage/Level3/layer_5.png");
        // strcpy(layerPaths3[5], "assets/Stage/Level3/layer_6.png");
        // strcpy(layerPaths3[6], "assets/Stage/Level3/layer_7.png");
        // user->sendMessage(new EventInitStage(layerPaths3));        
        // std::this_thread::sleep_for(std::chrono::milliseconds(4000));

        // char path6[100];
        // strcpy(path6, "assets/TransitionScreens/Stage3Cleared.JPG");
        // user->sendMessage(new EventEndStage(path6));
        // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        Event* event6 = new EventEndGame();
        response_t response7 = user->sendMessage(event6);


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

void ServerTransmitionManager::sendToUser(User* user, Event* event){
    response_t response = user->sendMessage(event);
    //TODO check response - loguear
}

void ServerTransmitionManager::sendToAllUsers(Event *event){

}
