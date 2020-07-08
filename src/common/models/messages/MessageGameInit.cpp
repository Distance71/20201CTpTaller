#include "MessageGameInit.h"

Event* MessageGameInit::deSerialize(){
    return (Event *) new EventGameInit(this->screenSizes_);
}

message_t MessageGameInit::getType(){
	return this->type_;
}

responseStatus_t MessageGameInit::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
    int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = server->getSocket()->sendMessage((void *&) this->screenSizes_ ,sizeof(this->screenSizes_));

	return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}

