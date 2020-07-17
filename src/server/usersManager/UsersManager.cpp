#include "UsersManager.h"

UsersManager::UsersManager(Server *serverOwn){
    this->serverOwn_ = serverOwn;
    this->lastId_ = 0;
    this->loggedUsersCount_ = 0;
}

UsersManager::~UsersManager(){}


Server* UsersManager::getServer(){
    return this-> serverOwn_;
}


bool UsersManager::isFullGame(){
    return this->loggedUsersCount_ == GameProvider::getQuantityPlayers();
}


void UsersManager::processEvent(Event* event){
    this->serverOwn_->processEvent(event);
}


void UsersManager::sendEventToNotLoggedUser(Id id, Event* event){
    this->users_[id]->sendEvent(event);
}


void UsersManager::sendEventToAllLogged(Event* event){
    for (auto user : this->loggedUsers_){
        user.second->sendEvent(event);
    }
}


void UsersManager::setLoginResponse(Id id,bool response,string username){
    if (response == true){
        User* user = this->users_[id];
        this->users_.erase(id);
        user->setLoggedIn();
        user->setUsername(username);
        
        bool found = false;
        for (auto loggedUser:this->loggedUsers_){
            if (loggedUser.second->getUsername() == username){
                loggedUsers_.erase(loggedUser.first);
                found= true;
                break;
            }
        }
        
        if(!found){
            this->loggedUsersCount_ ++;
        }
        
        this->loggedUsers_.emplace(id,user);
    }
}




bool UsersManager::isLoggedIn(string username ){
    for (auto loggedUser:this->loggedUsers_){
        if (loggedUser.second->getUsername() == username){
            return loggedUser.second->isLoggedIn();
        }
    }
    return false;
}



bool UsersManager::wasPreviouslyLogged(string username){
    for (auto loggedUser:this->loggedUsers_){
        if (loggedUser.second->getUsername() == username){
            return true;
        }
    }
    return false;
}


void UsersManager::acceptUser(){
    Id idUser = this-> lastId_;
    int newClientDescriptor = this->serverOwn_->getSocket()->acceptClient(); 
    if (newClientDescriptor < 0){
        Logger::getInstance()->log(ERROR, "Error al aceptar al cliente.");
        return;
    }
    Socket *socketNewUser = new Socket(newClientDescriptor);
    User* newUser = new User(this,socketNewUser);
    newUser->setConnection();
    newUser->setId(idUser);
    newUser->runSendingMessagesThread();
    newUser->runReceivingMessagesThread();
    this->users_.emplace(idUser,newUser);
    this->lastId_ ++;
    Logger::getInstance()->log(INFO, "Se ha conectado un usuario");
}


static void * acceptUsers (void* arg){ 
    Logger::getInstance()->log(DEBUG, "Se incia el hilo de detección de conexiones entrantes");
    UsersManager* manager = (UsersManager* ) arg; 
    Server* server = manager->getServer();
    cout << "Esperando jugadores..." << endl;
    while (server->isConnected()){
        usleep(100000);
        manager->acceptUser();        
    }
    Logger::getInstance()->log(DEBUG, "Se ha detenido el hilo de detección de conexiones entrantes");
    return nullptr;
}


void UsersManager::runAcceptUsersThread(){
    pthread_t acceptUsersThread;
    pthread_create(&acceptUsersThread,NULL,acceptUsers,this);
}

