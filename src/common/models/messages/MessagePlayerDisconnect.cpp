#include "MessagePlayerDisconnect.h"

Event* MessagePlayerDisconnect::deSerialize(){
    return (Event *) new EventPlayerDisconnect(this->id_);
}

message_t MessagePlayerDisconnect::getType(){
	return this->type_;
}