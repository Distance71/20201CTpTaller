#include "EventMapElementUpdate.h"
#include "../../../client/Client.h"

void EventMapElementUpdate::update() {
  if (!this->context_){
	  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventMapElementUpdate");
  }
  else{
    Client* client = (Client*) Event::context_;
    client->updateEntity(this->type_, this->position_);
    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventMapElementUpdate");
  }
}