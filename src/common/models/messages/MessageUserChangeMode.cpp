#include "MessageUserChangeMode.h"

Event* MessageUserChangeMode::deSerialize(){
    return (Event *) new EventUserChangeMode();
}

message_t MessageUserChangeMode::getType(){
	return this->type_;
}

responseStatus_t MessageUserChangeMode::serialize(){
    return OK;
}