#include "EventWriteLog.h"

Message* EventWriteLog::serialize() {
    return (Message *) new MessageLog(this->level_, this->message_);
}

void EventWriteLog::update() {
    if (!this->context_) Logger::getInstance()->log(ERROR, "Se seteo un evento sin contexto");

 cout << this->message_ << endl;
    Logger::getInstance()->log((LOG_LEVEL)this->level_, this->message_);
}