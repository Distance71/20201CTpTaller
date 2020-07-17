#include "MessageSceneAnimation.h"

Event* MessageSceneAnimation::deSerialize(){
    return (Event *) new EventSceneAnimation(this->scene_);
}

message_t MessageSceneAnimation::getType(){
	return this->type_;
}

sceneScreen_t MessageSceneAnimation::getScene(){
	return this->scene_;
}

responseStatus_t MessageSceneAnimation::serialize(){
    return OK;
}