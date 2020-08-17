#include "UsersManager.h"

UsersManager::UsersManager(Server *serverOwn){
    this->serverOwn_ = serverOwn;
    this->lastId_ = 0;
    this->sendingQueue_ = new BlockingQueue <Message*>();
    runSendingThread();
}

UsersManager::~UsersManager(){
    for (auto user: this->notLoggedInUsers_){
        if (user.second){
            delete user.second;
        }
    }
}


Server* UsersManager::getServer(){
    return this-> serverOwn_;
}


bool UsersManager::isFullGame(){
    return this->loggedInUsers_.size() == GameProvider::getQuantityPlayers();
}


void UsersManager::processEvent(Event* event){
    this->serverOwn_->processEvent(event);
}


void UsersManager::sendEventToNotLoggedUser(Id id, Event* event){
    this->notLoggedInUsers_[id]->sendMessage(event->serialize());
    delete event;
    
}


void UsersManager::sendEventToAllLogged(Event* event){
    this->sendingQueue_->push(event->serialize());
    delete event;
}

BlockingQueue <Message*> * UsersManager::getQueue(){
     return this->sendingQueue_;
 }

static void* sendMessages(void* arg){
    UsersManager* usersManager = (UsersManager*) arg;
    Server* server = usersManager->getServer();
    BlockingQueue <Message*> * sendingQueue = usersManager->getQueue();
    
    while(server->isConnected()){
        if(!sendingQueue->empty()){
            Message* message = sendingQueue->pop();
            usersManager->sendToAll(message);
            delete message;
        }
    }
}

void UsersManager::sendToAll(Message* message){
    for (auto user :this->loggedInUsers_){
        user.second->sendMessage(message);
    }
}

void UsersManager::sendEventToOneUserLogged(string username, Event* event){

    try {
        this->loggedInUsers_[username]->sendMessage(event->serialize());
    } catch (const std::out_of_range& oor){

    }
    
}

void UsersManager::runSendingThread(){
    pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);
}


responseStatus_t UsersManager::loginRequest(Id id,string username,string password){
    bool valid = GameProvider::isValidCredential(username,password);

    if (!valid){
         Logger::getInstance()->log(INFO, "No se le permite el acceso a un jugador ya que las credenciales no son validas");
        return ERROR_WRONG_CREDENTIALS;
    }


    User* user;
    User* exuser;
    

    //juego lleno
    if(this->isFullGame()){
        
        auto iter = loggedInUsers_.find(username);
        
        //si no estaba participando no entra
        if (iter ==  loggedInUsers_.end()){
            Logger::getInstance()->log(INFO, "No se le permite el acceso a un jugador ya que la partida está completa");
            return ERROR_FULL_GAME;
        }        

        
        // sino me fijo si esta conectado, si lo está no entra
        else if (iter->second->isConnected()){
            Logger::getInstance()->log(INFO, "No se le permite el acceso a un jugador ya que hay un usuario conectado con el mismo usuario");
            return ERROR_ALREADY_LOGGED_IN;
        }
        
        //sino puede volver a jugar y hay una reconexion
        else{     
            user = notLoggedInUsers_.find(id)->second;

            exuser = iter->second;
            loggedInUsers_.erase(iter->first);
            delete exuser;
            
            user->setUserName(username);           
            loggedInUsers_.emplace(username,user);
            this->informConnection(username);

            Logger::getInstance()->log(INFO, "Se reconecta el usuario: " + username);

            return OK;
        
        }
    
    }

    //Si el juego no está lleno
    
    else{
        auto iter = loggedInUsers_.find(username);
        
        // si no estaba jugando puede entrar
        if (iter ==  loggedInUsers_.end()){
            user = notLoggedInUsers_.find(id)->second;
            user->setUserName(username);
            loggedInUsers_.emplace(username,user);
            this->informConnection(username);
            Logger::getInstance()->log(INFO, "Se conecta el usuario:" + username);
            return OK;
        }

        // si ya se logueo y está conectado no entra
        else{
            if (iter->second->isConnected()){
                Logger::getInstance()->log(INFO, "No se le permite el acceso a un jugador ya que hay un usuario conectado con el mismo usuario");
                return ERROR_ALREADY_LOGGED_IN;
            }
        
        // si ya se logueo pero se desconectó entra
            else{
                exuser= iter->second;
                loggedInUsers_.erase(username);
                delete exuser;
                user = notLoggedInUsers_.find(id)->second;
                user->setUserName(username);
                loggedInUsers_.emplace(username,user);
                this->informConnection(username);
                Logger::getInstance()->log(INFO, "Se reconecta el usuario: " + username);
                return OK;
            }
        }
    }
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
    newUser->runReceivingMessagesThread();
    this->notLoggedInUsers_.emplace(idUser,newUser);
    this->lastId_ ++;

    unsigned int quantityPlayers = GameProvider::getQuantityPlayers();
    Event* event = new EventQuantityPlayers(quantityPlayers);
    this->sendEventToNotLoggedUser(idUser, event);    

    //usleep(500000);

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


void UsersManager::informDisconnection(string username){
    this->serverOwn_->informDisconnection(username);
}

void UsersManager::informConnection(string username){    
    this->serverOwn_->informConnection(username);
}