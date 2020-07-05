#include "EventMapElementDelete.h"
#include "../../../client/Client.h"

Message* EventMapElementDelete::serialize() {
    return (Message *) new MessageMapElementDelete(this->id_);
}

void EventMapElementDelete::update() {
  if (!this->context_)
	  Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

  ((Client *)context_)->getGameScreen()->deadEntity(this->id_);
}