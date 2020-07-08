#include "MessageLog.h"

Event* MessageLog::deSerialize(){
    return (Event *) new EventWriteLog(this->level_, this->message_);
}

message_t MessageLog::getType(){
	return this->type_;
}

responseStatus_t MessageLog::serialize(){
	if (!this->context_)
		Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

	Server*server = ((Server *)context_);
	int result1 = server->getSocket()->sendMessage((void *&) this->type_, sizeof(this->type_));
    int result2 = server->getSocket()->sendMessage((void *&) this->level_ ,sizeof(this->level_));
    int result3 = server->getSocket()->sendMessage((void *&) this->message_ ,sizeof(this->message_));
    
	return (result1 > 0 && result2>0 && result3>0) ? OK : ERROR_MESSAGE;

}