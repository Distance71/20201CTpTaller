#include "MessageGameOver.h"

Event* MessageGameOver::deSerialize(){
    return (Event *) new EventGameOver();
}

message_t MessageGameOver::getType(){
	return this->type_;
}

responseStatus_t MessageGameOver::serialize(){
    return OK;
}