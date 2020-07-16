#include "MessageMapElementUpdate.h"

Event* MessageMapElementUpdate::deSerialize(){
    return (Event *) new EventMapElementUpdate(this->elementType_, this->position_);
}

message_t MessageMapElementUpdate::getType(){
	return this->type_;
}

elementType_t MessageMapElementUpdate::getElementType(){
    return this->elementType_;
}

position_t MessageMapElementUpdate::getPosition(){
    return this->position_;
}

responseStatus_t MessageMapElementUpdate::serialize(){
    return OK;
}