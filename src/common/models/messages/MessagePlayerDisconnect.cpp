#include "MessagePlayerDisconnect.h"

Event* MessagePlayerDisconnect::deSerialize(){
    return (Event *) new EventPlayerDisconnect(this->id_);
}

message_t MessagePlayerDisconnect::getType(){
	return this->type_;
}

responseStatus_t MessagePlayerDisconnect::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
	int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
    int result2 = server->getSocket()->sendMessage((void *&) this->id_ ,sizeof(this->id_));
    return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}

