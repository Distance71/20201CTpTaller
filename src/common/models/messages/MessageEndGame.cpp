#include "MessageEndGame.h"

Event* MessageEndGame::deSerialize(){
    return (Event *) new EventEndGame();
}

message_t MessageEndGame::getType(){
	return this->type_;
}

responseStatus_t MessageEndGame::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
	int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));

	return (result1 > 0) ? OK : ERROR_MESSAGE;
}
 