#include "EventEndStage.h"

Message* EventEndStage::serialize() {
    return (Message *) new MessageEndStage(this->path_);
}

void EventEndStage::update() {
  if (!this->context_){
	  Logger::getInstance()->log(DEBUG, "No hay contexto para el evento EventEndStage");
  }
  else{
    Client* client = (Client *) Event::context_;
    client->setImage(this->path_);
    Logger::getInstance()->log(DEBUG, "Se ejecutó el evento EventEndStage");
  }
}