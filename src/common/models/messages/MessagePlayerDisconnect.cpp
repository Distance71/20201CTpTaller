#include "MessagePlayerDisconnect.h"

Event* MessagePlayerDisconnect::deSerialize(){
    return (Event *) new EventPlayerDisconnect(this->id_);
}

message_t MessagePlayerDisconnect::getType(){
	return this->type_;
}

responseStatus_t MessagePlayerDisconnect::serialize(){
    return OK;
}

size_t MessagePlayerDisconnect::getId(){
    return this->id_;
}