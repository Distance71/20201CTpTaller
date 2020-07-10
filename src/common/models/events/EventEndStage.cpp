#include "EventEndStage.h"

Message* EventEndStage::serialize() {
    return (Message *) new MessageEndStage(this->path_);
}

void EventEndStage::update() {
  if (!this->context_)
	  Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

  Client* client = (Client *) context_;
  client->setImage(this->path_);
}