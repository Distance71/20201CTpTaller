#include "MessageResponseLoginPlayer.h"

Event* MessageResponseLoginPlayer::deSerialize(){
    return (Event *) new EventResponseLoginPlayer(this->response_);
}

message_t MessageResponseLoginPlayer::getType(){
	return this->type_;
}

responseStatus_t MessageResponseLoginPlayer::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");
    
	Server*server = ((Server *)context_);
    int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
	int result2 = server->getSocket()->sendMessage((void *&) this->response_ ,sizeof(this->response_));
    return (result1 > 0 && result2>0) ? OK : ERROR_MESSAGE;
}