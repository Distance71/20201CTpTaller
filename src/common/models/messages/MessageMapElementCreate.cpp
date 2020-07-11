#include "MessageMapElementCreate.h"

Event* MessageMapElementCreate::deSerialize(){
    return (Event *) new EventMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

message_t MessageMapElementCreate::getType(){
	return this->type_;
}

responseStatus_t MessageMapElementCreate::serialize(){
    return OK;
}

size_t MessageMapElementCreate::getId(){
    return this->id_;
}

char* MessageMapElementCreate::getPath(){
    return this->imagePath_;
}

position_t MessageMapElementCreate::getPosition(){
    return this->position_;
}

spriteSize_t MessageMapElementCreate::getSpriteSize(){
    return this->spriteSize_;
}