#ifndef _MESSAGE_LOG_H_
#define _MESSAGE_LOG_H_

#include <iostream>
#include "Message.h"
#include "../events/EventWriteLog.h"
#include "../events/Event.h"
#include "../../types.h"

using namespace std;

#ifndef MAX_SIZE_MESSAGE
#define MAX_SIZE_MESSAGE 100
#endif

class MessageLog : public Message {

    private:
        size_t level_;
        char message_[MAX_SIZE_MESSAGE];    
        const message_t type_ = LOG;    

    public:
    	explicit MessageLog(int level, char message[MAX_SIZE_MESSAGE]) {
            level_ = level;
            for(size_t i = 0; i < MAX_SIZE_MESSAGE; i++){
                message_[i] = message[i];
            }
        };
        Event* deSerialize();
        message_t getType();
        responseStatus_t serialize();
        char* getMessage();
        size_t getLevel();
};

#endif // _MESSAGE_LOG_H_