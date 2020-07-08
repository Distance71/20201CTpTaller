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
        const message_t type_ = LOG;    

    public:
    	explicit MessageLog(int level, string message) : level_(level), message_(message) {}
        Event* deSerialize();
        message_t getType();
        responseStatus_t serialize() override;
};

#endif // _MESSAGE_LOG_H_