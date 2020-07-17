#include "User.h"

User::User(UsersManager* userManager,Socket* socket){
	this->usersManager_ = userManager;
	this->socket_ = socket;

	this->connected_ = true;
	this->sendingQueue_ = new BlockingQueue <Message*>();
	
	string username_ = "";

	this->logged_ = false;
	this->previouslyLogged_ = false;
}


User::~User() {
	delete this->sendingQueue_;
}

void User::setId(Id id){
	this->id_ = id;
}

Id User::getId(){
	return this->id_;
}


string User::getUsername(){
	return this->username_;
}


void User::setUsername(string username){
	this->username_ = username;
}


void User::setLoggedIn(){
	this->logged_ = true;
	this->previouslyLogged_ = true;
}

bool User::isLoggedIn(){
	return this->logged_;
}

void User::setConnection(){
	this->connected_= true;
}


void User::setDisconnection(){
	this->connected_ = false;
	this->logged_ = false;
}


bool User::isConnected(){
	return this->connected_;
}


Socket* User::getSocket(){
	return this->socket_;
}


UsersManager* User::getUsersManager(){
	return this->usersManager_;
}


void User::sendEvent(Event* event){
	this->sendingQueue_->push(event->serialize());
}


Message* User::getMessage(){
	if (!this->sendingQueue_->empty()){
		return this->sendingQueue_->pop();
	}
	return NULL;
}

static void* sendMessages(void* arg){
	Logger::getInstance()->log(DEBUG, "Se inicia hilo envíos para un usuario");
	User* user = (User*) arg;
	MessageSerializer serializer = MessageSerializer();
	Socket* socket = user->getSocket();
	
	while (user->isConnected()){
		Message* message = user->getMessage();
		if (message){;
			serializer.sendSerializedEvent(socket, message);
			delete message;
			usleep(10);
		}
	}
	Logger::getInstance()->log(DEBUG, "Se detiene hilo de envíos para un usuario");
	return nullptr;
}


void User::runSendingMessagesThread(){
	pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,sendMessages,this);
}


static void* receivingMessages(void * arg){
	Logger::getInstance()->log(DEBUG, "Se inicia el hilo de recepción para un usuario");
	
	User* user = (User*) arg;
	Socket* socket = user->getSocket();
	UsersManager* userManager = user->getUsersManager();
	MessageDeserializer deserealizer = MessageDeserializer();
	

	
	while(user->isConnected()){
		Event* event;
		response_t res = deserealizer.getReceivedMessage(socket,event);
		Id id = user->getId();
		
		if(!event){   
			if (res.status == DISCONNECTION) {
                Logger::getInstance()->log(INFO, "Se detecta desconexión del cliente.");
                Logger::getInstance()->log(DEBUG, "Se detiene el hilo de recepción para un usuario");
				user->setDisconnection();
                return nullptr;
            }
        }
		else{
			event->setOwn(id);
			userManager->processEvent(event);
		}	
	}
	Logger::getInstance()->log(DEBUG, "Se detiene el hilo del recepción para un usuario");
    return nullptr;
}


void User::runReceivingMessagesThread(){
	pthread_t sending_thread;
    pthread_create(&sending_thread,NULL,receivingMessages,this);
}
