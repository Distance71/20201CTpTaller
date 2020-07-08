#include "MessageUserMovement.h"

Event* MessageUserMovement::deSerialize(){
    return (Event *) new EventUserMovement(this->orientation_);
}

message_t MessageUserMovement::getType(){
	return this->type_;
}

responseStatus_t MessageUserMovement::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    Client* client = ((Client *)context_);
	
	int result1 = client->getTransmitionManager()->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = client->getTransmitionManager()->getSocket()->sendMessage((void *&) this->orientation_ ,sizeof(this->orientation_));
    return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}