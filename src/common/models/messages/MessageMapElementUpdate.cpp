#include "MessageMapElementUpdate.h"

Event* MessageMapElementUpdate::deSerialize(){
    return (Event *) new EventMapElementUpdate(this->id_, this->position_);
}

message_t MessageMapElementUpdate::getType(){
	return this->type_;
}

responseStatus_t MessageMapElementUpdate::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    Server*server = ((Server *)context_);
    int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = server->getSocket()->sendMessage((void *&) this->id_ ,sizeof(this->id_));
    int result3 = server->getSocket()->sendMessage((void *&) this->position_ ,sizeof(this->position_));
    return (result1 > 0 && result2>0 && result3>0) ? OK : ERROR_MESSAGE;
}