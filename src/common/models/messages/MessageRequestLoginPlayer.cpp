#include "MessageRequestLoginPlayer.h"

Event* MessageRequestLoginPlayer::deSerialize(){
    return (Event *) new EventRequestLoginPlayer(this->userName_, this->password_);
}

message_t MessageRequestLoginPlayer::getType(){
	return this->type_;
}

responseStatus_t MessageRequestLoginPlayer::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

    Client*client = ((Client *)context_);
	int result1 = client->getTransmitionManager()->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
    int result2 = client->getTransmitionManager()->getSocket()->sendMessage((void *&) this->userName_ ,sizeof(this->userName_));
    int result3 = client->getTransmitionManager()->getSocket()->sendMessage((void *&) this->password_ ,sizeof(this->password_));
    return (result1 > 0 && result2>0 && result3>0) ? OK : ERROR_MESSAGE;
}