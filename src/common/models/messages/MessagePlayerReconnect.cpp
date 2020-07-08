#include "MessagePlayerReconnect.h"

Event* MessagePlayerReconnect::deSerialize(){
    return (Event *) new EventPlayerReconnect(this->id_);
}

message_t MessagePlayerReconnect::getType(){
	return this->type_;
}

responseStatus_t MessagePlayerReconnect::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
	int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
    int result2 = server->getSocket()->sendMessage((void *&) this->id_ ,sizeof(this->id_));
    
    return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}