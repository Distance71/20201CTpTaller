#include "EventMapElementUpdate.h"
#include "../../../client/Client.h"

Message* EventMapElementUpdate::serialize() {
    return (Message *) new MessageMapElementUpdate(this->id_, this->position_);
}

void EventMapElementUpdate::update() {
  if (!this->context_)
	  Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

  int Xpos = this->position_.axis_x;
  int Ypos = this->position_.axis_y;
  orientation_t orientation = this->position_.orientation;
  ((Client *)context_)-> updateEntity(this->id_,Xpos,Ypos,orientation);
}