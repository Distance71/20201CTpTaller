#include "MessageAnimationInitStage.h"

Event* MessageAnimationInitStage::deSerialize(){
    return (Event *) new EventAnimationInitStage(this->path_);
}

message_t MessageAnimationInitStage::getType(){
	return this->type_;
}