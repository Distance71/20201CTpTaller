#include "MessageLog.h"

Event* MessageLog::deSerialize(){
     cout << this->message_ << "primero"<< endl;
    return (Event *) new EventWriteLog(this->level_, this->message_);
}