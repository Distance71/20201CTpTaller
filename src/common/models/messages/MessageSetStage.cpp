#include "MessageSetStage.h"

Event* MessageSetStage::deSerialize(){
    return (Event *) new EventSetStage(this->stage_);
}

message_t MessageSetStage::getType(){
	return this->type_;
}

stage_t MessageSetStage::getStage(){
	return this->stage_;
}

responseStatus_t MessageSetStage::serialize(){
    return OK;
}