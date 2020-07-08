#include "MessageMapElementCreate.h"

Event* MessageMapElementCreate::deSerialize(){
    return (Event *) new EventMapElementCreate(this->id_, this->imagePath_, this->position_, this->spriteSize_);
}

message_t MessageMapElementCreate::getType(){
	return this->type_;
}

responseStatus_t MessageMapElementCreate::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
    int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
    int result2 = server->getSocket()->sendMessage((void *&) this->id_ ,sizeof(this->id_));
    int result3 = server->getSocket()->sendMessage((void *&) this->imagePath_ ,sizeof(this->imagePath_));
    int result4 = server->getSocket()->sendMessage((void *&) this->position_ ,sizeof(this->position_));
    int result5 = server->getSocket()->sendMessage((void *&) this->spriteSize_ ,sizeof(this->spriteSize_));
	
    return (result1 > 0 && result2>0 && result3>0 && result4>0 && result5>0) ? OK : ERROR_MESSAGE;

}