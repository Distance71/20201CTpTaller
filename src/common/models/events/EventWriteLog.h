#ifndef EVENT_WRITE_LOG_H
#define EVENT_WRITE_LOG_H

#include "Event.h"
#include "../messages/MessageLog.h"
#include "../messages/Message.h"
#include "../../services/Logger.h"

using namespace std;

class EventWriteLog: public Event {

    private:
        int level_;
        string message_;     

    public:
        EventWriteLog(int level, string message) : level_(level), message_(message) {}
        
        Message* serialize();
        void update();
};

#endif