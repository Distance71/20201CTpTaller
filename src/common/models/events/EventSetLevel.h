#ifndef _EVENT_SET_LEVEL_H_
#define _EVENT_SET_LEVEL_H_

#include "Event.h"
#include "../messages/MessageSetLevel.h"
#include "../messages/Message.h"
#include "../../providers/GameProvider.h"
#include "../../services/Logger.h"
#include "../../../client/Client.h"

class EventSetLevel: public Event{

    private:
        level_t level_;
        
    public:
        EventSetLevel(level_t level) : level_(level){};

        Message* serialize();
        void update();

};

#endif
