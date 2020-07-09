#ifndef _MESSAGE_LOG_H_
#define _MESSAGE_LOG_H_

#include <iostream>
#include "Message.h"
#include "../events/EventWriteLog.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

#define MAX_MESSAGE 100

class MessageLog : public Message {

    private:
        int level_;
        char message_[MAX_MESSAGE];    
        const message_t type_ = LOG;    

    public:
    	explicit MessageLog(int level, char message[MAX_MESSAGE]) {
            level_ = level;
            for(size_t i = 0; i < MAX_MESSAGE; i++){
                message_[i] = message[i];
            }
        };
        Event* deSerialize();
        message_t getType();
        responseStatus_t serialize() {};
};

#endif // _MESSAGE_LOG_H_