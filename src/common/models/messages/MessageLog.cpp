#include "MessageLog.h"

Event* MessageLog::deSerialize(){
    return (Event *) new EventWriteLog(this->level_, this->message_);
}