#include "MessageBackgroundUpdate.h"

Event* MessageBackgroundUpdate::deSerialize(){
    return (Event *) new EventBackgroundUpdate(this->layer_, this->stage_, this->step_);
}

message_t MessageBackgroundUpdate::getType(){
	return this->type_;
}

int MessageBackgroundUpdate::getStep(){
	return this->step_;
}

responseStatus_t MessageBackgroundUpdate::serialize(){
    return OK;
}

layer_t MessageBackgroundUpdate::getLayer(){
	return this->layer_;
}

stage_t MessageBackgroundUpdate::getStage(){
	return this->stage_;
}