#include "User.h"

User::User(Socket *socket){
	this->socket_ = socket;
	this->connected_ = true;
	deserializer_ = new MessageDeserializer();
	serializer_ = new MessageSerializer();
}

User::User(string userName, string password){
	this->userName_ = userName;
	this->password_ = password;
	this->connected_ = true;
	deserializer_ = new MessageDeserializer();
	serializer_ = new MessageSerializer();
}

User::~User() {
	this->socket_ = nullptr;
	this->logged_ = false;
	this->connected_ = false;
	delete socket_;
	delete deserializer_;
	delete serializer_;
}

string User::getUserName(){
	return this->userName_;
}

string User::getPassword(){
	this->password_;
}

void User::setLoggedIn(){
	this->logged_ = true;
}

void User::setUserName(string userName){
	this->userName_ = userName;
}

void User::setPassword(string password){
	this->password_ = password;
}

void User::setCharacter(character_t character){
	this->character_ = character; 
}

character_t User::getCharacter(){
	return this->character_;
}

void User::setSocket(Socket *socket){
	this->socket_ = socket;
}

Socket* User::getSocket(){
	return this->socket_;
}

bool User::isConnected(){
	return this->connected_;
}

IdUser User::getId(){
	return this->userId_;
}

void User::setId(IdUser id){
	userId_ = id;
}

void User::setDisconnection(){
	this->socket_ = NULL;
	this->connected_ = false;
}

Event* User::receiveMessage(){
	Event* event;
	response_t response = deserializer_->getReceivedMessage(socket_, event); //Validar
	if(response.ok)
		return event;
	return nullptr;
}

response_t User::sendMessage(Event* event){
	return serializer_->sendSerializedEvent(this->socket_, event); //Send also, for consistence?
}