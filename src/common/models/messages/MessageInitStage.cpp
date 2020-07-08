#include "MessageInitStage.h"

Event* MessageInitStage::deSerialize(){
    return (Event *) new EventInitStage(this->layerPaths_);
}

message_t MessageInitStage::getType(){
	return this->type_;
}

responseStatus_t MessageInitStage::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    Server*server = ((Server *)context_);
    int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = server->getSocket()->sendMessage((void *&) this->layerPaths_ ,sizeof(this->layerPaths_));

	return result1 > 0  && result2>0? OK : ERROR_MESSAGE;
}