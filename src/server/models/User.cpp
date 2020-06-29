#include "User.h"

User::User(Socket *socket){
	this->socket_ = socket;
}

User::User(string userName, string password){
	this->userName_ = userName;
	this->password_ = password;
	this->connected_ = true;
}

User::~User() {
	this->socket_ = nullptr;
	this->logged_ = false;
	this->connected_ = false;
	delete socket_;
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

void User::setDisconnection(){
	this->socket_ = NULL;
	this->connected_ = false;
}

Message* User::receiveMessage(){
	return nullptr;//;MessageDeserializer::getReceivedMessage(this);
}

void User::sendMessage(Message* message){
	//return MessageSerializer::serializeMessage(message); //Send also, for consistence?
}