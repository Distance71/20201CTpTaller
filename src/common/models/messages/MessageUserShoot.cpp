#include "MessageUserShoot.h"

Event* MessageUserShoot::deSerialize(){
    return (Event *) new EventUserShoot();
}

message_t MessageUserShoot::getType(){
	return this->type_;
}

responseStatus_t MessageUserShoot::serialize(){
    return OK;
}
