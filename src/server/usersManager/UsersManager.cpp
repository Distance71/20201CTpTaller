#include "UsersManager.h"

UsersManager::UsersManager(Server *serverOwn){
    this->serverOwn_ = serverOwn;
    size_t maxUsers = GameProvider::getQuantityPlayers();
    this->maxUsers_ = maxUsers;
    pthread_mutex_init(&this->mutex_lastId_, NULL);
}

UsersManager::~UsersManager(){
    this->serverOwn_ = nullptr;
}

bool UsersManager::isFullGame(){
    return loggedUsers_ >= this->maxUsers_;
}

IdUser UsersManager::acceptUnloggedUser(){

    int newClientDescriptor = this->serverOwn_->getSocket()->acceptClient();
    if (newClientDescriptor < 0){
        Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        return 0;
    }
    
    pthread_mutex_lock(&this->mutex_lastId_);
    Socket *socketNewUser = new Socket(newClientDescriptor);
    
    User* newUser = new User(socketNewUser);
    this->users_[this->lastId_++] = newUser;

    this->serverOwn_->addPlayer(newUser);

    pthread_mutex_unlock(&this->mutex_lastId_); 

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


// unordered_map<IdUser, User *> UsersManager::getUsers(){
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