#include "EventRequestLoginPlayer.h"


EventRequestLoginPlayer::EventRequestLoginPlayer(char userName[MAX_SIZE_CREDENTIALS], char password[MAX_SIZE_CREDENTIALS]){
  this->userName_ = (char*) malloc(sizeof(char)* (MAX_SIZE_CREDENTIALS + 1));
  this->password_ = (char*) malloc(sizeof(char)* (MAX_SIZE_CREDENTIALS + 1));
  strcpy (this->userName_,userName);
  strcpy (this->password_,password);
}

Message* EventRequestLoginPlayer::serialize() {
    return (Message *) new MessageRequestLoginPlayer(this->userName_, this->password_);
}

void EventRequestLoginPlayer::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay conexto para el evento EventRequestLoginPlayer");
    }
    
    else{
      Server* server = (Server*) Event::context_;
      responseStatus_t res = server->loginRequest(this->own_,this->userName_,this->password_);
      cout << res << endl;
      EventResponseLoginPlayer* event = new EventResponseLoginPlayer(res);
      server->sendToUser(this->own_,event);
      cout << res << endl;
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventRequestLoginPlayer");
    }

    free(this->userName_);
    free(this->password_);
}
      