#include "MessageMapElementUpdate.h"

Event* MessageMapElementUpdate::deSerialize(){
    return (Event *) new EventMapElementUpdate(this->id_, this->position_);
}

message_t MessageMapElementUpdate::getType(){
	return this->type_;
}

responseStatus_t MessageMapElementUpdate::serialize(){
    return OK;
}