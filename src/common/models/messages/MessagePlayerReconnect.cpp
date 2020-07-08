#include "MessagePlayerReconnect.h"

Event* MessagePlayerReconnect::deSerialize(){
    return (Event *) new EventPlayerReconnect(this->id_);
}

message_t MessagePlayerReconnect::getType(){
	return this->type_;
}