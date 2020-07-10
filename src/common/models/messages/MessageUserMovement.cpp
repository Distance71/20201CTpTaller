#include "MessageUserMovement.h"

Event* MessageUserMovement::deSerialize(){
    return (Event *) new EventUserMovement(this->orientation_);
}

message_t MessageUserMovement::getType(){
	return this->type_;
}

responseStatus_t MessageUserMovement::serialize(){
    return OK;
}