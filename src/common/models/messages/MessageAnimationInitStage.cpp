#include "MessageAnimationInitStage.h"

Event* MessageAnimationInitStage::deSerialize(){
    return (Event *) new EventAnimationInitStage(this->path_);
}

message_t MessageAnimationInitStage::getType(){
	return this->type_;
}

responseStatus_t MessageAnimationInitStage::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	int result = context_->getTransmitionManager()->getSocket()->sendMessage((void *)path_, sizeof(path_));

	return result > 0 ? OK : ERROR_MESSAGE;
}
