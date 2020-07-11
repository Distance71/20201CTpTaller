#include "MessageEndStage.h"

Event* MessageEndStage::deSerialize(){
    return (Event *) new EventEndStage(this->path_);
}

message_t MessageEndStage::getType(){
	return this->type_;
}

responseStatus_t MessageEndStage::serialize(){
    return OK;
}

char* MessageEndStage::getPath(){
	return this->path_;
}