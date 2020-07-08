#include "MessageMapElementCreate.h"

Event* MessageMapElementCreate::deSerialize(){
    return (Event *) new EventMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

message_t MessageMapElementCreate::getType(){
	return this->type_;
}