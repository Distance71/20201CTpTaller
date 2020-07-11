#include "EventWriteLog.h"

Message* EventWriteLog::serialize() {
    return (Message *) new MessageLog(this->level_, this->message_);
}

void EventWriteLog::update() {
    Logger::getInstance()->log((LOG_LEVEL)this->level_, this->message_);
}