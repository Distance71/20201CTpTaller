#include "EventPlayerReconnect.h"

Message* EventPlayerReconnect::serialize() {
    return (Message *) new MessagePlayerReconnect(this->id_);
}

void EventPlayerReconnect::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventPlayerReconnect");
    }
    else{
      Client* client = (Client*) Event::context_;
      client->reconnect();
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventPlayerReconnect");
    }
}