#include "EventMapElementDelete.h"
#include "../../../client/Client.h"

Message* EventMapElementDelete::serialize() {
    return (Message *) new MessageMapElementDelete(this->id_);
}

void EventMapElementDelete::update() {
  if (!this->context_){
	  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventMapElementDelete");
  }
  else{
    Client* client = (Client*) Event::context_;
    client->deadEntity(this->id_);
    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventMapElementDelete");
  }
}