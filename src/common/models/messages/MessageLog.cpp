#include "MessageLog.h"

Event* MessageLog::deSerialize(){
    return (Event *) new EventWriteLog(this->level_, this->message_);
}

message_t MessageLog::getType(){
	return this->type_;
}

responseStatus_t MessageLog::serialize(){
    return OK;
}