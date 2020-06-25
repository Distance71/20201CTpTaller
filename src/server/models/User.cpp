#include "User.h"

User::User(string userName, string password){
	this->userName_ = userName;
	this->password_ = password;
}

string User::getUserName(){
	return this->userName_;
}

string User::getPassword(){
	this->password_;
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

void User::disconnect(){
	this->socket_ = NULL;
	this->connected_ = false;
}