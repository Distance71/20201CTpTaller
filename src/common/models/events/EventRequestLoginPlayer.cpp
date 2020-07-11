#include "EventRequestLoginPlayer.h"

Message* EventRequestLoginPlayer::serialize() {
    return (Message *) new MessageRequestLoginPlayer(this->userName_, this->password_);
}

void EventRequestLoginPlayer::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay conexto para el evento EventRequestLoginPlayer");
    }
    else{
      //completar
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventRequestLoginPlayer");
    }
}