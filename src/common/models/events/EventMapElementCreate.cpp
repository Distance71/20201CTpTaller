#include "EventMapElementCreate.h"
#include "../../../client/Client.h"

Message* EventMapElementCreate::serialize() {
    return (Message *) new MessageMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

void EventMapElementCreate::update() {
  if (!this->context_)
    Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    int Xsize= this->spriteSize_.width;
    int Ysize= this->spriteSize_.height;
    int Xpos = this->position_.axis_x;
    int Ypos = this->position_.axis_y;
    orientation_t orientation = this->position_.orientation;

  ((Client *)context_)->createEntity(this->id_,this->imagePath_,Xsize,Ysize,Xpos,Ypos,orientation);

}

