#include "MessagePlayerReconnect.h"

Event* MessagePlayerReconnect::deSerialize(){
    return (Event *) new EventPlayerReconnect(this->id_);
}

message_t MessagePlayerReconnect::getType(){
	return this->type_;
}

responseStatus_t MessagePlayerReconnect::serialize(){
    return OK;
}

size_t MessagePlayerReconnect::getId(){
    return this->id_;
}