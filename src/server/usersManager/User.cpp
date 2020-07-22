#include "User.h"

User::User(UsersManager* userManager,Socket* socket){
	this->usersManager_ = userManager;
	this->socket_ = socket;
	this->username_ = "";

	this->connected_ = true;
	this->sendingQueue_ = new BlockingQueue <Message*>();
}


User::~User() {
	delete this->socket_;
}


void User::setId(Id id){
	this->id_ = id;
}

void User::setUserName(string username){
	this->username_ = username;
}


Id User::getId(){
	return this->id_;
}

string User::getUserName(){
	return this->username_;
}

void User::setConnection(){
	this->connected_= true;
}


void User::setDisconnection(){
   Logger::getInstance()->log(INFO, "Se detecta desconexión del cliente " + this->username_);
	this->connected_ = false;
	if (this->username_ != "")
		this->usersManager_->informDisconnection(this->username_);
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


void User::sendMessage(Message* message){
	if(connected_){
		MessageSerializer serializer = MessageSerializer();
		serializer.sendSerializedEvent(this->socket_, message);
	}
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
		string userName = user->getUserName();
		if (res.status == DISCONNECTION || res.status==ERROR_CONNECTION) {
			Logger::getInstance()->log(DEBUG, "Se detiene el hilo de recepción para un usuario");
			user->setDisconnection();
			return nullptr;
        }
		else{
			event->setOwn(id);
			event->setNameOwn(userName);
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