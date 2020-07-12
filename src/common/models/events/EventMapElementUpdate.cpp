#include "EventMapElementUpdate.h"
#include "../../../client/Client.h"

Message* EventMapElementUpdate::serialize() {
    return (Message *) new MessageMapElementUpdate(this->id_, this->position_);
}

void EventMapElementUpdate::update() {
  if (!this->context_){
	  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventMapElementUpdate");
  }
  else{
    Client* client = (Client*) Event::context_;
    client -> updateEntity(this->id_, this->position_.axis_x, this->position_.axis_y, this->position_.orientation);
    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventMapElementUpdate");
  }
}