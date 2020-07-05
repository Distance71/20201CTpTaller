#ifndef _MESSAGE_LOG_H_
#define _MESSAGE_LOG_H_

#include <iostream>
#include "Message.h"
#include "../events/EventWriteLog.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

class MessageLog : public Message {

    private:
        int level_;
        string message_;        

    public:
    	explicit MessageLog(int level, string message) : level_(level), message_(message) {}
        Event* deSerialize();
};

#endif // _MESSAGE_LOG_H_