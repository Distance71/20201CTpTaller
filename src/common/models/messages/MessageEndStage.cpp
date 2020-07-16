#include "MessageEndStage.h"

Event* MessageEndStage::deSerialize(){
    return (Event *) new EventEndStage(this->scene_);
}

message_t MessageEndStage::getType(){
	return this->type_;
}

responseStatus_t MessageEndStage::serialize(){
    return OK;
}

sceneScreen_t MessageEndStage::getScene(){
	return this->scene_;
}