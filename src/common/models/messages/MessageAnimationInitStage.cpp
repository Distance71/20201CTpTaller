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

	Server*server = ((Server *)context_);
	int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = server->getSocket()->sendMessage((void *&) this->path_, sizeof(this->path_));

	return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}
 
