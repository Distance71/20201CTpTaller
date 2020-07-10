#include "MessageAnimationInitStage.h"

Event* MessageAnimationInitStage::deSerialize(){
    return (Event *) new EventAnimationInitStage(this->path_);
}

message_t MessageAnimationInitStage::getType(){
	return this->type_;
}

responseStatus_t MessageAnimationInitStage::serialize(){
    return OK;
}
