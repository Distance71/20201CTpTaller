#include "MessageSetLevel.h"

Event* MessageSetLevel::deSerialize(){
    return (Event *) new EventSetLevel(this->level_);
}

message_t MessageSetLevel::getType(){
	return this->type_;
}

level_t MessageSetLevel::getLevel(){
	return this->level_;
}

responseStatus_t MessageSetLevel::serialize(){
    return OK;
}