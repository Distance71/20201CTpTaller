#include "UsersManager.h"

UsersManager::UsersManager(Server *serverOwn){
    this->serverOwn_ = serverOwn;
    size_t maxUsers = GameProvider::getQuantityPlayers();
    this->maxUsers_ = maxUsers;
    pthread_mutex_init(&this->mutex_lastId_, NULL);

    // int pthreadCreateStatus =  pthread_create(&thread, nullptr, [](void *args)->void * {
    //     auto arguments = (argsThread_t *) args;
    //     auto *handler = (ServerTransmitionManager *) arguments->handler;
    //     auto *user = (User *) arguments->params;

    //     Logger::getInstance()->log(DEBUG, "Se va iniciar el ciclo del receptor transmitionManager");
    
    //     while (user->isConnected() && this->serverOwn_->isConnected()) {
    //         Logger::getInstance()->log(DEBUG, "Se va a recibir un evento en transmitionManager");
    //         Event *event = user->receiveMessage();
    //         if(!event){
    //             mtxErrno.lock();
    //             if (errno == ECONNREFUSED || errno == ENOTCONN || errno == ENOTSOCK) {
    //                 Logger::getInstance()->log(DEBUG, "Se detecta desconexión del cliente."+ to_string(user->getId()));
    //                 user->setDisconnection();
    //                 return nullptr;
    //             }
    //             mtxErrno.unlock();
    //             Logger::getInstance()->log(ERROR, "Se ha recibido un evento invalido. Se cerrará la conexión con el cliente");
    //             return nullptr;
    //         }
    //         Logger::getInstance()->log(DEBUG, "Se recibio un evento");
    //         cout << "se recibio un mensaje" << endl;
    //         //receivedMessagesQueue_->push(message);        
    //     }
        
    //     Logger::getInstance()->log(DEBUG, "Se termina correctamente el hilo del receptor del cliente " + to_string(user->getId()));
    //     return nullptr;
    // }, (void *) &args);


    // //Not handled
    // if(pthreadCreateStatus != 0) {
    //     string errorMessage = "No se pudo crear el hilo para manejar a los usuarios");
    //     Logger::getInstance()->log(ERROR, errorMessage);
    //     GameProvider::setErrorStatus(errorMessage);
    //     return;
    // }

    // Logger::getInstance()->log(DEBUG, "Se creó el hilo para manejar usuarios.");
}

UsersManager::~UsersManager(){
    this->serverOwn_ = nullptr;
}

bool UsersManager::isFullGame(){
    return loggedUsers_ >= this->maxUsers_;
}

Id UsersManager::acceptUnloggedUser(){

    int newClientDescriptor = this->serverOwn_->getSocket()->acceptClient();
    if (newClientDescriptor < 0){
        Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        return 0;
    }

    Socket *socketNewUser = new Socket(newClientDescriptor);
    User* newUser = new User(socketNewUser);

    pthread_mutex_lock(&this->mutex_lastId_);
    lastId_++;
    pthread_mutex_unlock(&this->mutex_lastId_);

    this->users_[this->lastId_] = newUser;

    this->serverOwn_->addPlayer(newUser);

    return this->lastId_;
}

// void UserManager::logInUser(User* User){

// }

    // unsigned int width = GameProvider::getWidth();
    // unsigned int height = GameProvider::getHeight();
    // MessageInitScreen initScreen = MessageInitScreen(width, height);
    // string dataString;
    // dataString = initScreen.getStringData();

    //newSocketClient->enviarMensaje(dataString.c_str(), sizeof(char) *dataString.size());
    
    
    // pthread_t newHilo;

    // argpthread argumentos;
    // argumentos.server = this;
    // argumentos.nroClient = this->clients.size();
    // argumentos.des = this->deserializer;

    // pthread_create(&newHilo, NULL, recibirInformacion, &argumentos);


// unordered_map<Id, User *> UsersManager::getUsers(){
//     return this->users_;
// }

// //Checks remains players
// bool UsersManager::playersConnected(IdPlayer id) {
	
// 	if(users_.size())
// 		return true;

// 	return false;

// 	for ( auto User = users_.begin(); it != users_.end(); ++it )
// 		if()
// 		User->first
// 		it->second;
// }

// void UsersManager::setPlayer(IdPlayer idPlayer, User* user){
//     users_[idPlayer] = user;
// }

// bool UsersManager::isGameFull(){
// 	size_t maxPlayers = GameProvider::getQuantityPlayers();

// 	return users_.size() == maxPlayers
// }

// User* UsersManager::getPlayer(IdPlayer idPlayer){
// 	if (users_.find(idPlayer) == users_.end())
// 		return NULL;

// 	return users_[idPlayer];
// }