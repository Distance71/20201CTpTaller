#include "EventPlayerDisconnect.h"

void EventPlayerDisconnect::update() {
    if (!this->context_){
		  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventPlayerDisconnect");
    }
    else{
      Client* client = (Client*) Event::context_;
      client->disconnect();
      Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventPlayerDisconnect");
    }
}