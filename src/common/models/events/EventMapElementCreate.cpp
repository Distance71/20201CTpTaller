#include "EventMapElementCreate.h"
#include "../../../client/Client.h"

Message* EventMapElementCreate::serialize() {
    return (Message *) new MessageMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

void EventMapElementCreate::update() {
  if (!this->context_)
    Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

  ((Client *)context_)->getGameScreen()->createEntity(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

