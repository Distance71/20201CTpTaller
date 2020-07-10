#ifndef EVENT_WRITE_LOG_H
#define EVENT_WRITE_LOG_H

#include "Event.h"
#include "../messages/MessageLog.h"
#include "../messages/Message.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"
using namespace std;

class MessageLog;

#ifndef MAX_MESSAGE_LOG
#define MAX_MESSAGE_LOG 100
#endif

class EventWriteLog: public Event {

    private:
        int level_;
        char message_[MAX_MESSAGE_LOG]; 

    public:
        explicit EventWriteLog(int level, char message[MAX_MESSAGE_LOG]) {
            for(size_t i = 0; i < MAX_MESSAGE_LOG; i++)
                message_[i] = message[i];
        }
        
        Message* serialize();
        void update();
};

#endif